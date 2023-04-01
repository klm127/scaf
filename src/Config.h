#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <map>

using namespace std; 
namespace fs = std::filesystem;

/*!
    GetFullExePath is used to get the actual fs location of scaf. This is different from where the current working directory is. It's often referred to as the process working directory. Apparently pwd functions are not cross-platform in the built-in libraries, so directives are used to make scaf compatible on linux and windows. 

    This is used to locate scaf's config in the same directory as scaf. 

    \returns A path for the folder containing scaf.exe 

    From https://stackoverflow.com/questions/50889647/best-way-to-get-exe-folder-path
*/
fs::path GetFullExePath();

/*!
    Config provides the functions and classes needed to load scaf's configuration. 

    When it is constructed, it looks for `scaf.config.json` in the `bin` folder. If it doesn't exist, it is created. If it is exists as a directory, a runtime error is thrown. 

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

        /*! Uses json library to read the configuration file. */
        void readConfig();

        /*! Returns the template directory read from the config file.*/
        fs::path getTemplateDir();

        /*! Gets the info for a given template. Returns empty string if no such info exists. */
        string getInfo(string template_name);
};

