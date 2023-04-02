#pragma once
/*!
    \file Template.h
    \brief Declarations for Template class.
    \author Karl Miller
    \date April 2023
    \deprecated
    \note Template is not currently used in the program!
*/
#include <string>
#include <vector>

using namespace std;

/*!
    Template holds information about a given template, including its folder location and saved-user info.

    NOTE: TEMPLATE IS NOT CURRENTLY ACTUALLY USED IN THE PROGRAM!

    Instead of instancing templates, scaf scans the directories within the root folder to get template names instead!
    As Config reads the saved program data, it instances Templates. (It doesn't!)

    Template has not been removed because it is well-tested and may be useful in a future refactor.
*/
class Template {
    private:
        /*! The absolute path of the template folder. */
        string path;
        /*! The name of the template that the user will use. This is the same as the final folder name, separated from the rest of the path. */
        string alias;
        /*! Optional user provided description. */
        string info;
        
    public:

        Template(string a_path, string an_alias, string some_info);
        Template(string a_path, string an_alias);
        Template(string a_path);
        Template();

        /*! Gets the template's absolute path on the file system. */
        string getPath();

        /*! Gets the template's name.*/
        string getAlias();

        /*! Sets the alias. */
        void setAlias(string an_alias);

        /*! If info is an empty string, returns a message saying that there is no info. */
        string getInfo();

        /*! Sets the template's info. */
        void setInfo(string some_info);

};