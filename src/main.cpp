#include <filesystem>
#include <iostream>
#include "Scaf.h"

using namespace std;

namespace fs = std::filesystem;

int main(int argc, char ** argv)
{
    // for(int i = 0; i < argc; i++) {
    //     cout << "\nArg[" << i << "] = " << argv[i];
    // }
    Scaf scaf = Scaf();
    scaf.Start(argc, argv);

    cout << endl;
    return 2023;

}