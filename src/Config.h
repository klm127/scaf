#pragma once
/*!
    \file Config.h
    \brief Declarations for Config class.
    \author Karl Miller
    \date April 2023
*/

#include <string>
#include <filesystem>
#include <iostream>
#include <map>

using namespace std; 
namespace fs = std::filesystem;

/*! The JSON key for the template directory. Should key a string. */
const string dirKey = "templateDir";
/*! The JSON key for the saved infos. Should key an object where the keys for all values are strings. */
const string infoKey = "infos";

/*!
    GetFullExePath is used to get the actual fs location of scaf. This is different from where the current working directory is. It's often referred to as the process working directory. Apparently pwd functions are not cross-platform in the built-in libraries, so directives are used to make scaf compatible on linux and windows. 

    This is used to locate scaf's config in the same directory as the scaf executable. 

    \returns A path for the folder containing scaf.exe 

    From https://stackoverflow.com/questions/50889647/best-way-to-get-exe-folder-path
*/
fs::path GetFullExePath();

/*!
    Config provides the functions and classes needed to load scaf's configuration. 

    When it is constructed, it looks for `scaf.config.json` in the process working directory. If it doesn't exist, it is created. If it is exists as a directory, a runtime error is thrown. 

    Otherwise, it parses that configuration file to load scaf's saved settings.
*/
class Config {
    private:
        /*! Path to the directory holding the configuration. (Will be the PWD of scaf.exe) */
        fs::path configPath;
        /*! Path to the directory holding the templates. Parsed from config file.*/
        fs::path templateDir;
        /*! A map of the info strings associated with templates. Parsed from config file. */
        map<string, string> infos;

    public:
        /*! Initializes the Config. Looks for scaf.config.json in the process working directory. If it doesn't exist, it is created. If it exists as a directory, a runtime error is thrown. */
        Config();
        /*! Generally the 0 parameter constructor should be called. Passing a custom configuration is useful for testing purposes. 
            \param customPath The path to configuration file.
        */
        Config(fs::path customPath);

        /*! Returns the path that was loaded at the time of Config's construction. */
        fs::path getPath();

        /*! Uses json library to read the configuration file. 

            If the json object is misconfigured, it may simply skip parsing that step and print an error to the console.
        */
        void readConfig();

        /*! Returns the template directory read from the config file.*/
        fs::path getTemplateDir();

        /*! Sets a new template directory. Will not be set and an error will be printed if the directory doesn't exist. 
            If the directory is relative, it will be converted to absolute. 

            \param newdir The new template directory. 
            \returns true if directory could be set. false otherwise.
        */
        bool setTemplateDir(fs::path newdir);

        /*! Checks if Config has a template directory loaded. */
        bool hasTemplateDir();

        /*! Gets the info for a given template. Returns empty string if no such info exists. */
        string getInfo(string template_name);

        /*! Sets the info for a given template. 
            \param key The name of the template.
            \param value The new info to set.
        */
        void setInfo(string key, string value);


        /*!
            Writes the config as a json. Called on program end to record updates in the config file. Pretty-prints the JSON with indentation.
        */
        void writeConfig();
};

