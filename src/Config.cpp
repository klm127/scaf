#ifdef _WIN32
#include <windows.h>
#elif
#include <unistd.h>
#endif 
#include <filesystem>
#include <fstream>

#include <Config.h>
#include <json.hpp>

using json = nlohmann::json;

#pragma region utility

fs::path GetFullExePath() {

#ifdef _WIN32
    wchar_t exe_path[MAX_PATH];
    GetModuleFileNameW(NULL, exe_path, MAX_PATH);
#else
    char a_path[PATH_MAX];
    ssize_t count = readLink( "/proc/self/exe" , a_path, PATH_MAX);
    szPath[count] = '\0';
#endif 

    return fs::path{ exe_path }.parent_path();
}

#pragma endregion utility

#pragma region constructors 

Config::Config() {
    fs::path c_path = GetFullExePath();
    c_path.append("scaf.config.json");
    if(fs::exists(c_path)) {
        if(fs::is_directory(c_path)) {
            cout << "\nDirectory error!";
            throw std::runtime_error(c_path.string() + " is a directory! Check the config folder!");
        } 
    } else { // Create the file if it doesn't exist.
        
        FILE * tfile = fopen(c_path.string().c_str(), "w");
        fputc('{', tfile);
        fputc('}', tfile);
        fclose(tfile);
    }
    configPath = c_path;
    templateDir = fs::path();
    infos = map<string, string>();
}

Config::Config(fs::path c_path) {
    if(fs::exists(c_path)) {
        if(fs::is_directory(c_path)) {
            cout << "\nDirectory error!";
            throw std::runtime_error(c_path.string() + " is a directory! Check the config folder!");
        }
    } else { // Create the file if it doesn't exist.
        FILE * tfile = fopen(c_path.string().c_str(), "w");
        fputc('{', tfile);
        fputc('}', tfile);
        fclose(tfile);
    }
    configPath = c_path;
    templateDir = fs::path();
    infos = map<string, string>();
}

#pragma endregion constructors

#pragma region getters_and_setters

fs::path Config::getTemplateDir() {
    return templateDir;
}

bool Config::setTemplateDir(fs::path new_path) {
    bool result = false;
    if(!fs::exists(new_path)) {
        cout << "\nThe path " << new_path << " doesn't exist!" << endl;
    }
    else if(!fs::is_directory(new_path)) {
        cout << "\nCan't set template directory to a non-directory!" << endl;
    } else {
        templateDir = fs::canonical(new_path);
        result = true;
    }
    return result;
}

string Config::getInfo(string key) {
    string result = infos[key];
    if(result.length() == 0) {
        result = "No info for " + key + ".";
    }
    return result;
}

void Config::setInfo(string key, string value) {
    infos[key] = value;
}

bool Config::hasTemplateDir() {
    if(templateDir.string().length() < 1) {
        return false;
    }
    return true;
}


fs::path Config::getPath() {
    return configPath;
}

#pragma endregion getters_and_setters

#pragma region readers_and_writers

void Config::readConfig() {
    json data;
    ifstream file;
    file.open(configPath);
    try {
        data = json::parse(file);
    } catch(const json::parse_error & ex) {
        cout << "Configuration is not a valid json file! Can't parse!" << ex.what() << endl;
        file.close();
        return;
    }
    file.close();
    if(data.contains(dirKey)) { // Parse the "templateDir" field of the configuration.
        json dirval = data[dirKey];
        if(!dirval.is_string()) {
            cout << "Config Error: " << dirKey << " is not a string. Skipping.\n";
        } else {
            string dirsval = dirval.get<string>();
            if(fs::is_directory(dirsval)) {
                templateDir = fs::path(data[dirKey]);
            } else {
                cout << "Config Error: " << dirKey << " is not a valid directory. Skipping. \n";
            }
        }
    };
    if(data.contains(infoKey)) { // Parse the "infos" field of the configuration.
        json infval = data[infoKey];
        if(!infval.is_object()) {
            cout << "Config Error: " << infoKey << " is not an object.\n";
        } else {
            for(auto& el : infval.items()) {
                if(!el.value().is_string()) {
                    cout << "Config Error: In " << infoKey << " " << el.key() << " is not a string. Skipping.\n";
                } else {
                    string elval = el.value().get<string>();
                    infos[el.key()] = elval;
                }
            }            
        }
    }
}


void Config::writeConfig() {
    json write = json();
    json infosjson = json();
    write[dirKey] = templateDir.string();
    for(const auto &[key, value] : infos) {
        infosjson[key] = value;
    }
    write[infoKey] = infosjson;
    ofstream file;
    file.open(configPath, ios::out);
    file << write.dump(4);
    file.close();
    cout << "\nUpdated config.\n";
}

#pragma endregion readers_and_writers

