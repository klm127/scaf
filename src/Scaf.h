#pragma once

#include <vector>
#include <filesystem>

#include "Config.h"

using namespace std;

/*! Converts a string to all lower-case in place.*/
void stringLower(string& s);

/*! Looks for a 'y' or 'n'. */
bool promptYN(bool default_yn);

/*!
    Scaf drives the program execution. It loads the config and parses the command line arguments into the correct commands. 
*/
class Scaf {
    public:
        /*! Constructor. */
        Scaf();
        /*! Constructor with config override. */
        Scaf(filesystem::path config_path);
        /*! Begins the parse process with the command-line args.
            \param argc The arg count.
            \param argv The arg values. 
            \return true for succesful parse.
        */
        bool Start(int argc, char ** argv);


    private:
        Config config;
        /*! Parses a help command. */
        bool Help(int index, vector<string>& args);

        /*! Processes the root command. */
        bool Root(int index, vector<string>& args);

        /*! Processes the add command.*/
        bool Add(int index, vector<string>& args);

        /*! Processes the load command. */
        bool Load(int index, vector<string>& args);

        /*! Processes the list command. */
        bool List(int index, vector<string>& args);

        /*! Prints overall program help. Occurs if no arguments are passed, 'help', or '?' is passed. */
        void printHelp();

        /*! Prints help for the root command. */
        void printHelpRoot();
        /*! Prints help for the add command. */
        void printHelpAdd();
        /*! Prints help for the info command. */
        void printHelpInfo();
        /*! Prints help for the set command. */
        void printHelpSet();
        /*! Prints help for the remove command. */
        void printHelpRemove();
        /*! Prints help for the load command. */
        void printHelpLoad();
        /*! Prints help for the rename command. */
        void printHelpRename();
        /*! Prints help for the list command. */
        void printHelpList();
    
};