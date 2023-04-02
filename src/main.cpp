/*!
    \file Filer.cpp
    \brief Program entry point.
    \author Karl Miller
    \date April 2023

    \mainpage scaf
    \version 1.0.1

    Created by Karl Miller for the Spring 2023 Code Jam at PennWest California. 

    Scaf is general purpose, command line, project initialization tool.

    Scaf is purpose-agnostic and can be used to start-up ("scaffold") any type of project that has a directory structure.

    Scaf works by maintaining directories of templates that the user supplies. When the user wants to scaffold a new project, they may use scaf to copy the contents from one of these directories into their current directory.

*/
#include <filesystem>
#include <iostream>
#include "Scaf.h"

using namespace std;

namespace fs = std::filesystem;

/*!
    Main is the program entry points.

    It passes the command line arguments along to an instance of Scaf for processing.

*/
int main(int argc, char ** argv)
{
    Scaf scaf = Scaf();
    bool result = scaf.Start(argc, argv);
    cout << endl;
    if(!result) {
        return 2023;
    } else {
        return 0;
    }
}