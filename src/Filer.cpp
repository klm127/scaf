#include "Filer.h"
#include <iostream>

int Filer::copyRecursive(fs::path from, fs::path to) {
    int count = 0;
    for(const auto& dir : fs::directory_iterator(from)) {
        if(dir.is_directory()) {
            if(dir.path().stem() != ".git") {
                fs::path to_path = to / dir.path().stem();
                fs::create_directory(to_path);
                count += copyRecursive(dir, to_path);
            }
        } else if(dir.is_regular_file()) {
            fs::path to_path = to / dir.path().filename().string();
            fs::copy_file(dir.path(), to_path);
            count++;
        }
    }
    return count;
}
bool Filer::isEmpty(fs::path check) {
    bool empty = true;
    for(const auto& dir : fs::recursive_directory_iterator(check)) {
        if(fs::is_directory(dir)) {
            if(dir.path().stem() != ".git") {
                empty = false;
                break;
            }  
        } else {
            empty = false;
            break;
        }
        
    }
    return empty;
}

bool Filer::fillMapWithDirectories(const fs::path & p, map<string, fs::path> & m) {
    bool result = true;
    if(!fs::exists(p)) {
        result = false;
    } else {
        for(const auto& dir : fs::directory_iterator(p)) {
            if(dir.is_directory()) {
                string stem = dir.path().stem().string();
                if(stem != ".git") {
                    m[stem] = dir;
                }
            }
        }
    }
    return result;
}

bool Filer::clearDir(fs::path p) {
    for(const auto& dir : fs::directory_iterator(p)) {
        if(dir.is_directory()) {
            string stem = dir.path().stem().string();
            if(stem != ".git") {
                fs::remove_all(dir.path());
            }
        } else {
            fs::remove(dir.path());
        }
    }
    return true;
}