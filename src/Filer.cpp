/*!
    \file Filer.cpp
    \brief Definitions for Filer namespace.
    \author Karl Miller
    \date April 2023
*/

#include "Filer.h"
#include <iostream>
#include <bits/stdc++.h>

Filer::copy_result Filer::copyRecursive(fs::path from, fs::path to) {
    Filer::copy_result result {0,0,false};
    for(const auto& dir : fs::directory_iterator(from)) {
        if(dir.is_directory()) {
            if(dir.path().stem() != ".git") {
                fs::path to_path = to / dir.path().stem();
                fs::create_directory(to_path);
                result.folderscopied += 1;
                Filer::copy_result inner = copyRecursive(dir.path(), to_path);
                result.filescopied += inner.filescopied;
                result.folderscopied += inner.folderscopied;
                if(inner.gitskipped) result.gitskipped = true;
            } else {
                result.gitskipped = true;
            }
        } else {
            fs::path to_path = to / dir.path().filename().string();
            fs::copy_file(dir.path(), to_path);
            result.filescopied += 1;
        }
    }
    return result;
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

bool Filer::fillVectorWithDirectories(const fs::path & p, vector<string> & v) {
    bool result;
    if(!fs::exists(p) || !(fs::is_directory(p))) {
        result = false;
    } else {
        result = true;
        for(const auto& dir : fs::directory_iterator(p)) {
            if(dir.is_directory()) {
                string stem = dir.path().stem().string();
                if(stem != ".git") {
                    v.push_back(stem);
                }
            }
        }
    }
    sort(v.begin(), v.end());
    return result;
}

bool Filer::fillVectorWithDirectories(const fs::path &p, vector<string>& v, string &filter_prefix) {
    bool result;
    if(!fs::exists(p) || !(fs::is_directory(p))) {
        result = false;
    } else {
        result = true;
        for(const auto& dir : fs::directory_iterator(p)) {
            if(dir.is_directory()) {
                string stem = dir.path().stem().string();
                if(stem != ".git") {
                    if(stem.rfind(filter_prefix, 0) == 0) {
                        v.push_back(stem);
                    }
                }
            }
        }
    }
    sort(v.begin(), v.end());
    return result;    
}

bool Filer::clearDir(fs::path p) {
    bool result;
    if(!fs::exists(p) || !(fs::is_directory(p))) {
        result = false;
    } else {
        result = true;
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
    }
    return result;
}