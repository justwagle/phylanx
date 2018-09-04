// Copyright (c) 2017-2018 Hartmut Kaiser
// Copyright (c) 2017 Alireza Kheirkhahan
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_PRIMITIVES_MUL_OPERATION_SEP_25_2017_0900PM)
#define PHYLANX_PRIMITIVES_MUL_OPERATION_SEP_25_2017_0900PM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>
#include <phylanx/ir/node_data.hpp>

#include <hpx/lcos/future.hpp>

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    class mul_operation
      : public primitive_component_base
      , public std::enable_shared_from_this<mul_operation>
    {
    protected:
        using operand_type = ir::node_data<double>;
        using operands_type =
            std::vector<operand_type, arguments_allocator<operand_type>>;

        hpx::future<primitive_argument_type> eval(
            primitive_arguments_type const& operands,
            primitive_arguments_type const& args) const;

    public:
        static match_pattern_type const match_data;

        mul_operation() = default;

        mul_operation(primitive_arguments_type&& operands,
            std::string const& name, std::string const& codename);

        hpx::future<primitive_argument_type> eval(
            primitive_arguments_type const& args) const override;

    private:
        enum struct stretch_operand { neither, lhs, rhs };

        primitive_argument_type mul0d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul0d(operands_type&& ops) const;
        primitive_argument_type mul0d0d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul0d0d(operands_type&& ops) const;
        primitive_argument_type mul0d1d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul0d2d(
            operand_type&& lhs, operand_type&& rhs) const;

        primitive_argument_type mul1d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul1d(operands_type&& ops) const;
        primitive_argument_type mul1d0d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul1d1d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul1d1d(operands_type&& ops) const;
        primitive_argument_type mul1d2d(
            operand_type&& lhs, operand_type&& rhs) const;

        primitive_argument_type mul2d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d(operands_type&& ops) const;
        primitive_argument_type mul2d0d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d1d(
            operand_type&& lhs, operand_type&& rhs) const;
        stretch_operand get_stretch_dimension(
            std::size_t lhs, std::size_t rhs) const;
        primitive_argument_type mul2d2d_no_stretch(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_lhs_both(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_rhs_both(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_lhs_row_rhs_col(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_lhs_row(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_lhs_col_rhs_row(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_rhs_row(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_lhs_col(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d_rhs_col(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d(
            operand_type&& lhs, operand_type&& rhs) const;
        primitive_argument_type mul2d2d(operands_type&& ops) const;
    };

    inline primitive create_mul_operation(hpx::id_type const& locality,
        primitive_arguments_type&& operands,
        std::string const& name = "", std::string const& codename = "")
    {
        return create_primitive_component(
            locality, "__mul", std::move(operands), name, codename);
    }
}}}

#endif
