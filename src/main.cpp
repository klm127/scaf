#include <filesystem>
#include <iostream>
#include "Scaf.h"

using namespace std;

namespace fs = std::filesystem;

int main(int argc, char ** argv)
{
    Scaf scaf = Scaf();
    scaf.Start(argc, argv);
    return 2023;

}