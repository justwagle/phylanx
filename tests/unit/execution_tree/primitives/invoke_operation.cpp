//   Copyright (c) 2017 Hartmut Kaiser
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <phylanx/phylanx.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/util/lightweight_test.hpp>

void test_invoke_operation(char const* expr, double expected)
{
    auto p = phylanx::execution_tree::generate_tree(expr);

    HPX_TEST_EQ(expected, phylanx::execution_tree::numeric_operand(p).get()[0]);
}

int main(int argc, char* argv[])
{
    test_invoke_operation(R"(
        block(
            define(x, 3.14),
            x
        )
    )", 3.14);

    // variables can be invoked as nullary functions
    test_invoke_operation(R"(
        block(
            define(x, 3.14),
            x()
        )
    )", 3.14);

    test_invoke_operation(R"(
        block(
            define(y, x, x + 1),
            y(3.0)
        )
    )", 4.0);

    test_invoke_operation(R"(
        block(
            define(add, x, y, x + y),
            add(41.0, 1.0)
        )
    )", 42.0);

    test_invoke_operation(R"(
        block(
            define(add, x, y, x + y),
            define(x1, 41.0),
            define(x2, 1.0),
            add(x1, x2)
        )
    )", 42.0);

    return hpx::util::report_errors();
}

