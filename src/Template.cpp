#include "Template.h"
#include <filesystem>

Template::Template(string a_path, string an_alias, string some_info) {
    path = a_path;
    alias = an_alias;
    info = some_info;
}
Template::Template(string a_path, string an_alias) {
    path = a_path;
    alias = an_alias;
    info = "";

}
Template::Template(string a_path) {
    path = a_path;
    info = "";
    filesystem::path extractor = filesystem::path(a_path);
    alias = extractor.stem().string();
}
Template::Template() {
    path = "";
    info = "";
    alias = "";
}
string Template::getPath() {
    return path;
}
string Template::getAlias() {
    return alias;
}
void Template::setAlias(string new_alias) {
    alias = new_alias;
}
string Template::getInfo() {
    if(info.length() < 1) {
        return "No information provided for " + alias + ".";
    } else {
        return info;
    }
}
void Template::setInfo(string some_info) {
    info = some_info;
}