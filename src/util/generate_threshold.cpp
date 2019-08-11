// Copyright (c) 2019 Bibek Wagle
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>

#include <fstream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
double null_function()
{
    return 0.0;
}
HPX_PLAIN_ACTION(null_function, null_action)
///////////////////////////////////////////////////////////////////////////////

int hpx_main(int argc, char** argv)
{
    int multiplier = 2000;
    int interval = 350000;

    {
        const std::uint64_t count = 1000000;
        const hpx::id_type here = hpx::find_here();
        std::vector<hpx::future<double>> futures;
        futures.reserve(count);

        // start the clock
        hpx::util::high_resolution_timer walltime;
        for (std::uint64_t i = 0; i < count; ++i)
        {
            futures.push_back(hpx::async<null_action>(here));
        }
        hpx::wait_all(futures);
        const double duration = walltime.elapsed();

        double us = 1e6 * duration / count;
        interval = us * multiplier;
    }

    char* filename = argv[1];
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        outfile << "//  Copyright (c) 2019 Bibek Wagle\n"
                << "//\n"
                << "//  Distributed under the Boost Software License, "
                << "Version 1.0. (See accompanying\n"
                << "//  file LICENSE_1_0.txt or copy "
                << "at http://www.boost.org/LICENSE_1_0.txt)\n"
                << "#if !defined(PHYLANX_INLINING_THRESHOLD_HPP_AUTOGEN)\n"
                << "#define PHYLANX_INLINING_THRESHOLD_HPP_AUTOGEN\n"
                << "\n"
                << "#define THRESHOLD " << interval << "\n\n"
                << "#endif\n";
    }
    else
    {
        std::cout << "Can not open file";
        return hpx::finalize();
    }

    outfile.close();
    return hpx::finalize();
}

int main(int argc, char** argv)
{
    return hpx::init(argc, argv);
}
