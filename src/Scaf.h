#pragma once
/*!
    \file Scaf.h
    \brief Declarations for Scaf class.
    \author Karl Miller
    \date April 2023
*/
#include <vector>
#include <filesystem>

#include "Config.h"
#include "Filer.h"

using namespace std;

/*! Converts a string to all lower-case in place.*/
void stringLower(string& s);

/*! Looks for a 'y' or 'n'. */
bool promptYN(bool default_yn);

/*! Prints a copy result on 3 lines with correct pluralization.
    \param copied The result of a recursive directory copy.
*/
void printCopyResult(Filer::copy_result & copied);

/*!
    Scaf drives the program execution. It loads the config and parses the command line arguments into the correct commands. 

    \brief Parses and executes the command line arguments.
*/
class Scaf {
    public:
        /*! Constructor. */
        Scaf();
        /*! Constructor with config override. For use with testing.
            \param config_path A different configuration path to provide to the Config object.
        */
        Scaf(filesystem::path config_path);
        /*! Begins the parse process with the command-line args.
            \param argc The arg count.
            \param argv The arg values. 
            \return True for succesful parse. False if there were errors. 
        */
        bool Start(int argc, char ** argv);


    private:
        Config config;
        /*! Parses a help command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Help(int index, vector<string>& args);

        /*! Processes the root command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Root(int index, vector<string>& args);

        /*! Processes the add command.
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Add(int index, vector<string>& args);

        /*! Processes the load command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Load(int index, vector<string>& args);

        /*! Processes the list command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool List(int index, vector<string>& args);

        /*! Processes the info command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Info(int index, vector<string>& args);

        /*! Processes the set command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Set(int index, vector<string>& args);

        /*! Processes the remove command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Remove(int index, vector<string>& args);

        /*! Processes the rename command. 
            \param index Index of the first unparsed argument.
            \param args The argument list from the command line.
        */
        bool Rename(int index, vector<string>& args);

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