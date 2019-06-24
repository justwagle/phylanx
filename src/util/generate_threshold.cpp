#include<iostream>
#include<fstream>

int main(int argc, char** argv)
{
    char* filename = argv[1];
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile){
    outfile<<"#define THRESHOLD 42454424";
    }
    else
    {
        std::cout<<"Can not open file";
        return -1;
    }
    outfile.close();
    return 0;
}