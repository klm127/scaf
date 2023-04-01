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

fs::path Config::getPath() {
    return configPath;
}

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

fs::path Config::getTemplateDir() {
    return templateDir;
}

string Config::getInfo(string key) {
    return infos[key];
}

