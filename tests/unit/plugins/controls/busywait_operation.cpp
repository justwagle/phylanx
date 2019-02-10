// Copyright (c) 2019 Bibek Wagle
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <phylanx/phylanx.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/util/lightweight_test.hpp>

#include<cstdint>
#include <utility>
#include <vector>

void test_busywait()
{
    phylanx::execution_tree::primitive num_samples =
            phylanx::execution_tree::primitives::create_variable(
                    hpx::find_here(), phylanx::ir::node_data<std::int64_t>(42));

    phylanx::execution_tree::primitive busywait =
            phylanx::execution_tree::primitives::create_busywait(
                    hpx::find_here(),
                    phylanx::execution_tree::primitive_arguments_type{ std::move(num_samples)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
            busywait.eval();

    auto result = phylanx::execution_tree::extract_integer_value(f.get());

    HPX_TEST_EQ(
            phylanx::ir::node_data<std::int64_t>(blaze::DynamicVector <std::int64_t>{42}),
            result);
}

int main(int argc, char* argv[])
{
    test_busywait();
    return hpx::util::report_errors();
}
