#include <iostream>
#include <string>

#include "Scaf.h"
#include "Filer.h"

#pragma region utility

void stringLower(string & s) {
    for(char& c : s) {
        c = tolower(c);
    }
}

bool promptYN(bool default_yn) {
    cout << "y/n?";
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

        } else if(arguments[0] == "info") {

        } else if(arguments[0] == "set") {

        } else if(arguments[0] == "remove") {

        } else if(arguments[0] == "rename") {

        }
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
        cout << "\nSet new template directory to " << target << ".";
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
                bool overwrite = promptYN(true);
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
        cout << "\nAdded " << alias << " to your templates.";
        config.setInfo(alias, infotxt);
        config.writeConfig();
    }
    
    return result;
}

#pragma endregion parse


#pragma region endpoint

void Scaf::printHelp() {
    cout <<   "\n                            ----------------- ";
    cout <<   "\n                           |      scaf       |";
    cout <<   "\n                            ----------------- ";
    
    cout << "\n\n scaf is a command line utility for quickly scaffolding any type of project.";
    cout <<   "\n It enables you to save project templates (scaffolds) in a special folder on your hard drive.";
    cout <<   "\n When you want to create a project using one of these templates, scaf will copy the contents";
    cout <<   "\n of the template into the folder you want to scaffold.";

    cout << "\n\n     Commands:  root, add, info, set, remove, help, load\n";

    if(!config.hasTemplateDir()) {
        cout << "\n Warning: You do not currently have a template directory loaded.";
        cout << "\n To use scaf, you must first set a template directory with the root command.\n";
    }

    cout << "\n Use `scaf help <command>` for more information about a specific command.\n";
}

void Scaf::printHelpRoot() {
    cout << "\n Scaf: Help for the root command:\n"
     << "\n\tSyntax: scaf root { . | subdir}\n"
     << "\n\tSets the root template directory. This is where your templates will be saved."
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
     << "\n\tSyntax: scaf list \n"
     << "\n\tLists all available templates.\n";
}

#pragma endregion endpoint