#pragma once
/*!
    \file Filer.h
    \brief Declarations for Filer namespace.
    \author Karl Miller
    \date April 2023
*/
#include <filesystem>
#include <map>
#include <vector> 
#include <functional>
using namespace std;
namespace fs = std::filesystem;


/*!
    Filer provides functions wrapping various filesystem operations, such as copyRecursive and isEmpty, used by Scaf.

    Particularly, Filer ignores `.git` folders when determining whether a directory is empty and when copying recursively.

    It also provides functions for getting information about the contents of a folder.

    \brief Performs some filesystem operations and queries.
*/
namespace Filer {

    /*!
        Provides data about a copy operation.

        \brief Provides data about a recursive copy operation.

        Returned by Filer::copyRecursive.
    */
    typedef struct {
        /*! The number of files copied.*/
        int filescopied;
        /*! The number of folders copied.*/
        int folderscopied;
        /*! Whether a '.git' folder was skipped. */
        bool gitskipped;
    } copy_result;
    /*! 
        Recursively copies all files and folders in from to directory to.

        Excludes .git folder and subdirs. 

        \pre from and to must be existing directories.
        \param from The directory to copy from.
        \param to The directory to copy to.
        \return The number of files copied.
    */
    copy_result copyRecursive(fs::path from, fs::path to);

    /*!
        Checks whether a given directory is empty. (Excluding .git folder.)
        \param checkdir The directory to examine.
        \return Whether the given directory is empty.
    */
    bool isEmpty(fs::path checkdir);

    /*!
        Clears a directory of all its contents, except for '.git' folder.
        \param dirToClear The directory to clear of contents.
        \returns true if path was valid and not a directory, false otherwise.
    */
    bool clearDir(fs::path dirToClear);

    /*! Fills a map in-place with directory names inside of path.
        \param p The path to use to populate the map.
        \param m The map to fill in-place.
        \returns true if path as valid and not a directory, false otherwise.
    */
    bool fillMapWithDirectories(const fs::path &p, map<string, fs::path>& m);

    /*! Fills a vector in-place with directory names inside of path, then sorts the vector. 
        \param p The path to use to fill the vector.
        \param v The vector to fill in-place.
        \returns true if path was valid and not a directory, false otherwise.
    */
    bool fillVectorWithDirectories(const fs::path &p, vector<string>& m);

    /*! Fills a vector in-place with directory names inside of path, then sorts the vector. 
        Overload allows passing a string function to prefix-filter the names.
        \param p The path to use to fill the vector.
        \param v The vector to fill in-place.
        \param filter_prefix A function to test each directory name. Directory names will only be added to v if callback(dirname) == true.
        \returns true if path was valid and not a directory, false otherwise.
    */
    bool fillVectorWithDirectories(const fs::path &p, vector<string>& v, string &filter_prefix);
}