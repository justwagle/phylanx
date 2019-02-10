//  Copyright (c) 2019 Bibek Wagle
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <phylanx/config.hpp>
#include <phylanx/ir/node_data.hpp>
#include <phylanx/plugins/controls/busywait_operation.hpp>

#include <hpx/include/lcos.hpp>
#include <hpx/include/naming.hpp>
#include <hpx/include/util.hpp>
#include <hpx/throw_exception.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace phylanx { namespace execution_tree { namespace primitives
        {
            ///////////////////////////////////////////////////////////////////////////
            match_pattern_type const busywait::match_data =
                    {
                            match_pattern_type{
                                    "busywait",
                                    std::vector<std::string>{"busywait(_1)"},
                                    &create_busywait, &create_primitive<busywait>, R"(
            start, end, nelements
            Args:

                start (number) : the start of the numeric range
                end (number) : the end of the numeric range
                nelements (int) : the number of elements

            Returns:

            An array with the requested number of elements, the first "
            of which is `start`, and the last is `end`.)",
                                    true
                            }
                    };

            ///////////////////////////////////////////////////////////////////////////
            busywait::busywait(primitive_arguments_type&& args,
                               std::string const& name, std::string const& codename)
                    : primitive_component_base(std::move(args), name, codename)
            {}

            ///////////////////////////////////////////////////////////////////////////
            primitive_argument_type busywait::busywait_main(
                    std::uint64_t delay_ns) const
            {
                    blaze::DynamicVector<std::int64_t> result(1, delay_ns);
                    if (delay_ns == 0)
                        return primitive_argument_type{std::move(result)};

                    std::uint64_t start = hpx::util::high_resolution_clock::now();

                    while (true)
                    {
                        // Check if we've reached the specified delay.
                        if ((hpx::util::high_resolution_clock::now() - start) >= delay_ns)
                            break;
                    }
                    return primitive_argument_type{std::move(result)};
            }

                        ///////////////////////////////////////////////////////////////////////////
            hpx::future<primitive_argument_type> busywait::eval(
                    primitive_arguments_type const& operands,
                    primitive_arguments_type const& args, eval_context ctx) const
            {
                if (operands.size() != 1)
                {
                    HPX_THROW_EXCEPTION(hpx::bad_parameter,
                                        "phylanx::execution_tree::primitives::busywait",
                                        generate_error_message(
                                                "the busywait primitive requires exactly one "
                                                "argument."));
                }

                for (std::size_t i = 0; i != operands.size(); ++i)
                {
                    if (!valid(operands[i]))
                    {
                        HPX_THROW_EXCEPTION(hpx::bad_parameter,
                                            "busywait::eval",
                                            generate_error_message(
                                                    "at least one of the arguments passed to "
                                                    "busywait is not valid."));
                    }
                }

                auto this_ = this->shared_from_this();
                return hpx::dataflow(hpx::launch::sync, hpx::util::unwrapping(
                        [this_ = std::move(this_)](std::uint64_t time)
                                -> primitive_argument_type
                        {
                            return this_->busywait_main(
                                    std::move(time));
                        }),
                        scalar_integer_operand(operands[0], args, name_, codename_, ctx));
            }
        }}}
