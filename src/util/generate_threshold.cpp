// Copyright (c) 2019 Bibek Wagle
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
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
                << "#if !defined(PHYLANX_INLINING_THRESHOLD_HPP)\n"
                << "#define PHYLANX_INLINING_THRESHOLD_HPP\n"
                << "\n"
                << "#define THRESHOLD 350000\n\n"
                << "#endif\n";
    }
    else
    {
        std::cout << "Can not open file";
        return -1;
    }
    outfile.close();
    return 0;
}
