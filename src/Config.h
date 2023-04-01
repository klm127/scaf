#pragma once

#include <string>
#include <filesystem>
#include <iostream>

using namespace std; 
namespace fs = std::filesystem;

fs::path GetFullExePath();

/*!
    Config provides the functions and classes needed to load scaf's configuration. 
*/
class Config {
    private:

    public:
    Config();

};

