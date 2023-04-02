# What is Scaf

Scaf is general purpose, command line, project initialization tool.

Scaf is purpose-agnostic and can be used to start-up ("scaffold") any type of project that has a directory structure.

Scaf works by maintaining directories of templates that the user supplies. When the user wants to scaffold a new project, they may use scaf to copy the contents from one of these directories into their current directory.

# About the Author

Scaf was made by Karl Miller for the 2023 PennWest California Spring Code Jam. 

# Commands

`scaf root { . | subdir }` Makes the current directory or provided subdirectory the root for scaf templates to be saved. This command needs to be used to pick a template directory before scaf will become functional.

`scaf add { { . | subdir} { alias { infotxt } }}` Create a scaf template from the current directory or subdirectory, and optionally change the name for templating (alias) and add info text. 

`scaf load <template> { subdirectory }` Scaffold one of your templates into the currect directory or the subdirectory if supplied.

`scaf list` List the available templates.

`scaf info <template>` Get a description of the given template.

`scaf set <template> <info>` Set the information for a template that can be referenced later.

`scaf remove <template>` Remove a given template.

`scaf rename <template> <newname>` Rename a given template. Info will also be moved over.


`scaf help <command>` Get help about scaf.

# Compiling, Running

Run `make folders` To make the `/bin` and `/obj` folders.

Run `make` to create `bin/scaf.exe`

Run `make test` to create `./test.exe`

Add the `bin` folder to your system path to access scaf from anywhere on your computer.

# Configuration

`scaf` will populate its own configuration. However, it is possible to manually edit `scaf.conf.json` if desired. This may be useful if you want to add a bunch of 'info' parameters at once, as templates without infos will be listed with empty strings. Shown below is an example configuration object.

```json
{
    "templateDir": "C:\\MyScafs",
    "infos": {
        "js1": "A simple node JS project I set up.",
        "cpp": "c++ with a basic makefile and unit testing framework.",
        "js2": "A webpacked JS project.",
        "ts": "A typescript and webpack project.",
        "goserv": "A go server."
    }

}
```

`scaf.config.json` will be placed in the same directory where `scaf.exe` is located.

# Dependencies

`lib/QUnit.hpp` A lightweight C++ testing framework. [Project Homepage](https://qunit.sourceforge.net/)
`lib/json.hpp` nlohmann/json's JSON parsing library. [Project Homepage](https://github.com/nlohmann/json)

