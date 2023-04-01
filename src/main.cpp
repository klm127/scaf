#include <filesystem>
#include <iostream>
#include <Config.h>

using namespace std;

namespace fs = std::filesystem;

int main(int argc, char ** argv)
{
    std::cout << "\nArgv[0] = " << argv[0];
    std::cout << "\nCurrent path is " << fs::current_path();
    std::cout << "\nProc path is " << GetFullExePath();
    return 2023;

}