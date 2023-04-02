/*!
    \file Scaff.cpp
    \brief Definitions for Scaff (command execution) class.
    \author Karl Miller
    \date April 2023
*/
#include <iostream>
#include <string>
#include <map>

#include "Scaf.h"
#include "Filer.h"

#pragma region utility

void stringLower(string & s) {
    for(char& c : s) {
        c = tolower(c);
    }
}

bool promptYN(bool default_yn) {
    cout << "y/n? ";
    char c = (char) getchar(); 
    bool result = default_yn;
    if(c == 'y' || c == 'Y') {
        result = true;
    } else if(c == 'n' || c == 'N') {
        result = false;
    } else {
        if(default_yn == true) {
            cout << "\nDefaulting to 'y'.";
        } else {
            cout << "\nDefaulting to 'n'.";
        }
    }
    return result;
}

#pragma endregion utility

#pragma region constructors

Scaf::Scaf() {
    config = Config();
    config.readConfig();
}

Scaf::Scaf(filesystem::path config_path) {
    config = Config(config_path);
    config.readConfig();
}

#pragma endregion constructors

#pragma region parse

bool Scaf::Start(int argc, char ** argv) {
    bool result = false;
    if(argc < 2) {
        printHelp();
        result = true;
    } else {
        vector<string> arguments(argv + 1, argv+argc);
        stringLower(arguments[0]);
        if(arguments[0] == "help" || arguments[0] == "?") {
            result = Help(1, arguments);
        } else if(arguments[0] == "root") {
            result = Root(1, arguments);
        } else if(arguments[0] == "add") {
            result = Add(1, arguments);
        } else if(arguments[0] == "load") {
            result = Load(1, arguments);
        } else if(arguments[0] == "list") {
            result = List(1, arguments);
        } else if(arguments[0] == "info") {
            result = Info(1, arguments);
        } else if(arguments[0] == "set") {
            result = Set(1, arguments);
        } else if(arguments[0] == "remove") {
            result = Remove(1, arguments);
        } else if(arguments[0] == "rename") {
            result = Rename(1, arguments);
        } else {
            result = false;
            cout << "\n" << arguments[0] << " is not a recognized command.";
        }
    }
    if(!result) {
        cout << "\n scaf finished with errors.";
    }
    return result;
}

bool Scaf::Help(int index, vector<string>& args) {
    if(index >= (int) args.size()) {
        printHelp();
    } else {
        stringLower(args[index]);
        if(args[index] == "root") {
            printHelpRoot();
        } else if(args[index] == "add") {
            printHelpAdd();
        } else if(args[index] == "info") {
            printHelpInfo();
        } else if(args[index] == "set") {
            printHelpSet();
        } else if(args[index] == "remove") {
            printHelpRemove();
        } else if(args[index] == "load") {
            printHelpLoad();
        } else if(args[index] == "rename") {
            printHelpRename();
        } else if(args[index] == "list") {
            printHelpList();
        } else {
            cout << "\nI don't have help on that topic.\n";
        }
    }
    return true;
}

bool Scaf::Root(int index, vector<string>& args) {
    fs::path target;
    if(index == (int) args.size()) {
        target = fs::current_path();
    } else {
        // stripQuotes(args[index]);
        if(args[index] == ".") {
            target = fs::current_path();
        } else {
            target = fs::current_path() / args[index];
        }
        index++;
        if(index == (int) args.size()) {
            cout << "\nToo many parameters. Skipping extras.";
        }
    }
    bool result = config.setTemplateDir(target);
    if(result) {
        cout << "\nSet new root template directory to " << target << ".";
        config.writeConfig();
    } else {
        cout << "\nFailed to execute command root.";
    }
    return result;
}

bool Scaf::Add(int index, vector<string>& args) {
    fs::path target;
    fs::path transfer_to;
    string alias;
    string infotxt = "";
    bool result = true;

    // Parse the arguments.
    if(index == (int) args.size()) {
        target = fs::current_path();
        alias = target.stem().string();
    } else {
        if(args[index] == ".") {
            target = fs::current_path();
            alias = target.stem().string();
        } else {
            // stripQuotes(args[index]);
            target = fs::current_path() / args[index];
            alias = args[index];
        }
        index++;
        if(index < (int) args.size()) {
            // stripQuotes(args[index]);
            stringLower(args[index]);
            alias = args[index];
            index++;
            if(index < (int) args.size()) {
                infotxt = args[index];
                if(index == (int) args.size()) {
                    cout << "\nToo many parameters. Skipping extras.";
                }
            }
        }
    }

    // Execute the command. 
    if(config.hasTemplateDir()) {
        if(fs::is_directory(target)) {
            transfer_to = config.getTemplateDir() / alias;
            bool ok_to_transf = true;
            if(fs::exists(transfer_to)) {
                cout << "\nA template with that alias already exists.";
                cout << "\nOverwrite? ";
                bool overwrite = promptYN(false);
                if(overwrite) {
                    cout << "\nOverwriting " << alias << ".";
                    fs::remove_all(transfer_to);
                    ok_to_transf = true; 
                } else {
                    cout << "\nCanceling execution of add command.";
                    ok_to_transf = false;
                    result = false;
                }
            }
            if(ok_to_transf) {
                try {
                    fs::create_directory(transfer_to);
                } catch(const fs::filesystem_error& ex) {
                    cout << "\nFailed to create directory " << transfer_to;
                    result = false;
                }
                if(result) {
                    int n_copied = Filer::copyRecursive(target, transfer_to);
                    // TODO: More detailed copy data; copyRecursive could return a struct. Can exceptions be thrown by copyRecursive? How should they be handled?
                    cout << "\nCopied " << n_copied << " files.";
                }
            }
        } else {
            cout << "\n" << target << " is not a directory.";
            result = false;
        }
    } else {
        cout << "\nNo root directory is set.";

    }

    // Write the config file, print result message. 
    if(!result) {
        cout << "\nFailed to execute command add.";
    } else {
        cout << "\nAdded '" << alias << "' to your templates.";
        config.setInfo(alias, infotxt);
        config.writeConfig();
    }
    
    return result;
}

bool Scaf::Load(int index, vector<string>& args) {
    bool result;
    fs::path target;
    string source_alias;
    fs::path source_path;

    // Parse the arguments
    if(index == (int) args.size()) {
        result = false;
        cout << "\nYou must supply a template to the load command.";
    } else {
        source_alias = args[index];
        index++;
        if(index == (int) args.size()) {
            target = fs::current_path();
        } else {
            if(args[index] == ".") {
                target = fs::current_path();
            } else {
                target = args[index];
            }
            index++;
            if(index >= (int) args.size()) {
                cout << "\nToo many parameters. Skipping extras.";
            }
        }
    }

    // Execute the command
    if(fs::is_directory(target)) {
        if(!config.hasTemplateDir()) {
            result = false;
            cout << "\nYou must first set a template directory with scaf root.";
        } else {
            map<string, fs::path> m = map<string, fs::path>();
        
            result = Filer::fillMapWithDirectories(config.getTemplateDir(), m);
            if(!result) {
                result = false;
                cout << "\nCouldn't load the template directory! Try setting again with scaf root.";
            } else {
                result = m[source_alias].string().size() > 0;
                
                if(!result) {
                    cout << "\nCouldn't locate the template " << source_alias << ".";
                } else {
                    
                    bool canfill = true;
                    if(!Filer::isEmpty(target)) {
                        cout << "\nTarget " << target << " is not empty.";
                        cout << "\nClear directory? ";
                        canfill = promptYN(false);
                        if(canfill) {
                            canfill = Filer::clearDir(target);
                            cout << "\nCleared directory.";
                        }
                    }
                    if(canfill){
                        source_path = m[source_alias];
                        Filer::copyRecursive(source_path, target);
                        result = true;
                    } else {
                        cout << "\nCan't load to full directory.";
                        result = false;
                    }
                }
                
            }
        }
    } else {
        cout << "\n" << target << " is not a directory!"; 
        result = false;
    }

    // Print the result.

    if(result) {
        cout << "\nLoaded template " << source_alias << " to " << target;
    } else {
        cout << "\nFailed to execute command load.";
    }
    
    return result;
}

bool Scaf::List(int index, vector<string>& args) {
    bool result;
    string filter = "";
    vector<string> dirnames = vector<string>();
    if(index < (int) args.size()) {
        filter = args[index];
        index++;
        if(index < (int) args.size()) {
            cout << "\nToo many parameters. Skipping extras.";
        }
    }

    if(!config.hasTemplateDir()) {
        result = false;
        cout << "\nYou must first set a template directory with scaf root.";
    } else {
        if(filter.size() > 0) {
            cout << "\nFiltering templates starting with '" << filter << "'.";
            Filer::fillVectorWithDirectories(config.getTemplateDir(), dirnames, filter);
        } else {
            Filer::fillVectorWithDirectories(config.getTemplateDir(), dirnames);
        }
        if(dirnames.size() > 0) {
            result = true;
        } else {
            if(filter.size() > 0) {
                cout << "\nThere are no directories in root " << config.getTemplateDir() << " matching filter "
                << filter << ".";
            } else {
                cout << "\nThere are no directories in root " << config.getTemplateDir() << ".";
                cout << "\nAdd at least one template first with scaf add.";
                result = false;

            }
        }
    }
    
    if(result) {
        cout << "\nListing available templates.\n\n";
        cout << right << setw(15) << "Template" << "   ";
        cout << left << setw(30) << "Info" << endl;
        cout << "  -------------   --------------------------------------" << endl;
        for(auto dir : dirnames) {
            cout << right << setw(15) << dir << "   ";
            cout << left << setw(30) << config.getInfo(dir) << endl;
        }
    } else {
        cout << "\nFailed to execute command list.";
    }
    return result;

}

bool Scaf::Info(int index, vector<string>& args) {
    bool result = true;
    string target;

    // parse arguments
    if(index == (int) args.size()) {
        cout << "\nNo template parameter supplied.";
        result = false;
    } else {
        target = args[index];
        index++;
        if(index < (int) args.size()) {
            cout << "\nToo many parameters. Skipping extras.";
        }
    }

    if(result) {
        if(!config.hasTemplateDir()) {
            cout << "\nNo template directory set in config. Use scaf root to set your root directory.";
            result = false;
        } else {
            map<string, fs::path> m = map<string, fs::path>();
            result = Filer::fillMapWithDirectories(config.getTemplateDir(), m);
            if(!result) {
                cout << "\nRoot is an invalid directory. Try setting it again.";
            } else {
                if(m[target].string().size() < 1) {
                    cout << "\n" << target << " does not refer to a valid template in root!";
                    result = false;
                } else {
                    cout << "\nInfo for template '" << target << "':\t";
                    string info = config.getInfo(target);
                    if(info.size() < 1) {
                        cout << "No info for " + target + ".";
                    } else {
                        cout << info;
                    }
                }
            }

        }
    }
    
    if(!result) {
        cout << "\nFailed to execute command info.";
    }
    return result;
}

bool Scaf::Set(int index, vector<string>& args) {
    bool result = true;
    string target;
    string newinfo;
    if(index == (int) args.size()) {
        cout << "\nNo template parameter provided!";
        result = false;
    } else {
        target = args[index];
        index ++;
        if(index == (int) args.size()) {
            newinfo = "";
        } else {
            newinfo = args[index];
            index++;
            if(index < (int) args.size()) {
                cout << "\nToo many parameters. Skipping extras.";
            }
        }
    }

    if(result) {
        if(!config.hasTemplateDir()) {
            cout << "\nNo root directory set. Use scaf root to set a root directory for templates.";
            cout << "\nInfo will be available once root is set and template with that name is added. ";
        } else {
            map<string, fs::path> m = map<string, fs::path>();
            if(!Filer::fillMapWithDirectories(config.getTemplateDir(), m)) {
                cout << "\nThere was a problem loading the root directory. Use scaf root to set a root directory for templates.";
                cout << "\nInfo will be available once root is set and template with that name is added. ";
            } else {
                if(m[target].string().size() < 1) {
                    cout << "\nCouldn't locate template " << target << ".";
                    cout << "\nInfo will be available once a template with that name is added.";
                } 
            }
        }
    }

    if(result) {
        cout << "\nSaving info for " << target << ".";
        config.setInfo(target, newinfo);
        cout << "\nExecuted command set.";
        config.writeConfig();
    } else {
        cout << "\nFailed to execute command set.";
    }
    return result;
}

bool Scaf::Remove(int index, vector<string>& args) {
    bool result = true;
    string target; 

    // parse
    if(index == (int) args.size()) {
        cout << "\nNo template parameter provided!";
        result = false;
    } else {
        target = args[index];
        index++;
        if(index < (int) args.size()) {
            cout << "\nToo many parameters. Skipping extras.";
        }
    }

    if(result) {
        if(!config.hasTemplateDir()) {
            cout << "\nNo root directory set. Use scaf root to set a root directory for templates.";
            result = false;
        } else {
            map<string, fs::path> m = map<string, fs::path>();
            if(!Filer::fillMapWithDirectories(config.getTemplateDir(), m)) {
                cout << "\nThere was a problem loading the root directory. Use scaf root to set a root directory for templates.";
                result = false;
            } else {
                if(m[target].string().size() < 1) {
                    cout << "\nCouldn't find template " << target << ".";
                    result = false;
                } else {
                    fs::path p = m[target];
                    try {
                        fs::remove_all(p);
                        cout << "\nRemoved " << p;
                        config.setInfo(target, "");
                        cout << "\nCleared info for " << target << ".";
                    } catch(const fs::filesystem_error& ex) {
                        cout << "\nFilesystem error when trying to remove " << p << "!";
                        cout << ex.what();
                        result = false;
                    }
                }
            }
        }
    }

    if(!result) {
        cout << "\nFailed to execute command remove.";
    } else {
        cout << "\nExecuted command remove.";
        config.writeConfig();
    }
    return result;
}

bool Scaf::Rename(int index, vector<string>& args) {
    bool result = true;
    string target;
    string new_name;

    if(index == (int) args.size()) {
        cout << "\nRemove command requires parameters!";
        result = false;
    } else {
        target = args[index];
        index++;
        if(index == (int) args.size()) {
            cout << "\nRemove command requires new name parameter!";
            result = false; 
        } else {
            new_name = args[index];
            index++;
            if(index < (int) args.size()) {
                cout << "\nToo many parameters. Skipping extras.";
            }

        }
    }

    if(target == new_name) {
        cout << "\n" << target << " already has the name " << new_name << "!";
        result = false;
    }

    if(result) {
        if(!config.hasTemplateDir()) {
            cout << "\nNo root directory set. Use scaf root to set a root directory for templates.";
            result = false;
        } else {
            map<string, fs::path> m = map<string, fs::path>();
            if(!Filer::fillMapWithDirectories(config.getTemplateDir(), m)) {
                cout << "\nThere was a problem loading the root directory. Use scaf root to set a root directory for templates.";
                result = false;
            } else {
                fs::path val = m[target];
                if(val.string().size() < 1) {
                    cout << "\nNo template found with name '" << target << "'!";
                    result = false;
                } else {
                    fs::path to = config.getTemplateDir() / new_name;
                    if(fs::exists(to)) {
                        cout << "\nA template with name '" << to << "' already exists!\nOverwrite? ";
                        result = promptYN(false);
                        if(result) {
                            try {
                                fs::remove_all(to);
                                cout << "\nRemoved " << to;
                            } catch(const fs::filesystem_error& ex) {
                                cout << "\nError while removing " << to << "!\n" << ex.what();
                                result = false;
                            }
                        }
                    }
                    if(result) {
                        try {
                            fs::create_directory(to);
                        } catch(const fs::filesystem_error& ex) {
                            cout << "\nError while creating " << to << "!\n" << ex.what();
                            result = false;
                        }
                    }
                    if(result) {
                        try {
                            int ncopied = Filer::copyRecursive(val, to);
                            cout << "\nCopied " << ncopied << " files.";
                        } catch(const fs::filesystem_error& ex) {
                            cout << "\nError copying files! \n" << ex.what();
                            result = false;
                        }
                    }
                    if(result) {
                        try {
                            fs::remove_all(val);
                            cout << "\nRemoved " << val << ".";
                        } catch(const fs::filesystem_error& ex) {
                            cout << "\nError removing " << val << "!\n" << ex.what();
                            result = false;
                        }
                    }

                }
            }
        }
    }

    if(result) {
        cout << "\nExecuted command rename '" << target << "' to '" << new_name << "'.";
        config.setInfo(new_name, config.getInfo(target));
        config.setInfo(target, "");
        config.writeConfig();

    } else {
        cout << "\nFailed to execute command remove.";
    }

    return result;
}
#pragma endregion parse


#pragma region print

void Scaf::printHelp() {
    cout <<   "\n                            ----------------- ";
    cout <<   "\n                           |      scaf       |";
    cout <<   "\n                            ----------------- ";
    
    cout << "\n\n scaf is a command line utility for quickly scaffolding any type of project.";
    cout <<   "\n It enables you to save project templates (scaffolds) in a special folder on your hard drive.";
    cout <<   "\n When you want to create a project using one of these templates, scaf will copy the contents";
    cout <<   "\n of the template into the folder you want to scaffold.";

    cout << "\n\n     Commands:  root, add, load, list, info, set, remove, rename\n";

    if(!config.hasTemplateDir()) {
        cout << "\n Warning: You do not currently have a template directory loaded.";
        cout << "\n To use scaf, you must first set a template directory with the root command.\n";
    }

    cout << "\n Use `scaf help <command>` for more information about a specific command.\n";
}
void Scaf::printHelpRoot() {
    cout << "\n Scaf: Help for the root command:\n"
     << "\n\tSyntax: scaf root { . | subdir}\n"
     << "\n\tRegisters the root template directory. This is where your templates will be saved."
     << "\n\tIf no subdir is provided, scaf will use the current directory as the root.\n";
}
void Scaf::printHelpAdd() {
    cout << "\n Scaf: Help for the add command:\n"
     << "\n\tSyntax: scaf add { { . | subdir} { alias { infotxt } }}\n"
     << "\n\tCreates a template from the current directory or a subdirectory."
     << "\n\tIf a subdirectory is provided, you may also provide an alias."
     << "\n\tIf an alias is provided, you may also provide info text."
     << "\n\tIf no alias is provided, the template will be named after the first word in the directory."
     << "\n\tIf no subdir is provided, scaf will create a template from the current directory.\n";
}
void Scaf::printHelpInfo() {
    cout << "\n Scaf: Help for the info command:\n"
     << "\n\tSyntax: scaf info <template>\n"
     << "\n\tPrints info for a template."
     << "\n\tInfo is a string that you have previously set with the set command."
     << "\n\tIt's useful for remembering what a template is.\n";
}
void Scaf::printHelpSet() {
    cout << "\n Scaf: Help for the set command:\n"
     << "\n\tSyntax: scaf set <template> {infotext}\n"
     << "\n\tSets the info text for a template."
     << "\n\tYou can check this info later with the info command."
     << "\n\tIt's useful for remembering what a template is.\n";
}
void Scaf::printHelpRemove() {
    cout << "\n Scaf: Help for the remove command:\n"
     << "\n\tSyntax: scaf remove <template>\n"
     << "\n\tRemoves a template from your root."
     << "\n\tUse this when a template has outlived its usefulness.\n.";

}
void Scaf::printHelpLoad() {
    cout << "\n Scaf: Help for the load command:\n"
     << "\n\tSyntax: scaf load <template> { . | subdir } \n"
     << "\n\tLoads a template named <template> from your root."
     << "\n\tCopies all files and folders in <template> into the given directory."
     << "\n\tUse load to load up a scaffold.\n.";
}
void Scaf::printHelpRename() {
    cout << "\n Scaf: Help for the load command:\n"
     << "\n\tSyntax: scaf rename <template> <newname> \n"
     << "\n\tRenames a template.\n";
}
void Scaf::printHelpList() {
    cout << "\n Scaf: Help for the list command:\n"
     << "\n\tSyntax: scaf list {filter}\n"
     << "\n\tLists all available templates."
     << "\n\tIf filter is provided, only lists those that start with filter.\n";
}

#pragma endregion print