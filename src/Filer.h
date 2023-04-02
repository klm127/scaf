#pragma once

#include <filesystem>
#include <map>
#include <vector> 
#include <functional>
using namespace std;
namespace fs = std::filesystem;



namespace Filer {

    /*!
        Provides data about a copy operation.

        Returned by Filer::copyRecursive.
    */
    typedef struct {
        /*! The number of files copied.*/
        int filescopied;
        /*! The number of folders copied.*/
        int folderscopied;
        /*! Whether a '.git' folder was skipped. */
        bool gitskipped;
        /*! The time it took. */
        double time_taken;
    } copy_result;
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