#pragma once

#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

namespace Filer {
    /*! 
        Recursively copies all files and folders in from to directory to.

        Excludes .git folder and subdirs. 

        \pre from and to must be existing directories.
        \param from The directory to copy from.
        \param to The directory to copy to.
        \return The number of files copied.
    */
    int copyRecursive(fs::path from, fs::path to);

    /*!
        Checks whether a given directory is empty. (Excluding .git folder.)
        \return Whether the given directory is empty.
    */
    bool isEmpty(fs::path checkdir);
}