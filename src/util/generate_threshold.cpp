//  Copyright (c) 2019 Bibek Wagle
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>

#include <vector>

///////////////////////////////////////////////////////////////////////////////
double null_function()
{
    return 0.0;
}
HPX_PLAIN_ACTION(null_function, null_action)

///////////////////////////////////////////////////////////////////////////////
int hpx_main(int argc, char* argv[])
{
    char* filename = argv[1];
    std::ofstream outfile;
    outfile.open(filename);

    if (outfile)
    {
        const std::uint64_t count = 1000000;
        const hpx::id_type here = hpx::find_here();
        std::vector<hpx::future<double>> futures;
        futures.reserve(count);

        // start the clock
        hpx::util::high_resolution_timer walltime;
        for (std::uint64_t i = 0; i < count; ++i)
            futures.push_back(hpx::async<null_action>(here));
        hpx::wait_all(futures);
        const double duration = walltime.elapsed();
        double us = 1e6 * duration / count;
        int interval = us * 2000;
        // hpx::cout<<us<<hpx::flush<<hpx::endl;
        // hpx::cout<<int(us*2000)<<hpx::flush<<hpx::endl;
        outfile << "#define THRESHOLD ";
        outfile << interval;
    }
    else
    {
        hpx::cout << "Can not open file";
        return -1;
    }
    outfile.close();
    return hpx::finalize();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Initialize and run HPX.
    return hpx::init(argc, argv);
}
