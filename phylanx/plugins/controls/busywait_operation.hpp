// Copyright (c) 2019 Bibek Wagle
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHYLANX_BUSYWAIT_PRIMITIVE_H
#define PHYLANX_BUSYWAIT_PRIMITIVE_H


#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/node_data_helpers.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>
#include <phylanx/ir/node_data.hpp>

#include <hpx/lcos/future.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
        {
            class busywait
                    : public primitive_component_base
                            , public std::enable_shared_from_this<busywait>
            {
            protected:
                hpx::future<primitive_argument_type> eval(
                        primitive_arguments_type const& operands,
                        primitive_arguments_type const& args,
                        eval_context ctx) const override;

            public:
                static match_pattern_type const match_data;

                busywait() = default;

                busywait(primitive_arguments_type&& args,
                         std::string const& name, std::string const& codename);

            private:
                primitive_argument_type busywait_main(std::uint64_t time) const;

            };

            inline primitive create_busywait(hpx::id_type const& locality,
                                             primitive_arguments_type&& operands,
                                             std::string const& name = "", std::string const& codename = "")
            {
                return create_primitive_component(
                        locality, "busywait", std::move(operands), name, codename);
            }
        }}}

#endif
