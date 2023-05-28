_Scaff, a universal project scaffolding tool_

# What is Scaf

Scaf is general purpose, command line, project initialization tool.

Scaf is purpose-agnostic and can be used to start-up ("scaffold") any type of project that has a directory structure.

Scaf works by maintaining directories of templates that the user supplies. When the user wants to scaffold a new project, they may use scaf to copy the contents from one of these directories into their current directory.

# Links

- [YouTube Demo](https://www.youtube.com/watch?v=kLVdjXp3JyA)
- [Blog Post](https://www.quaffingcode.com/scaf-code-jam)
- [Generated Documentation](http://www.quaffingcode.com/scaf/html/index.html)

# Use Cases

Scaf is useful for anyone who makes projects in directories, especially if they have ever found themselves recreating a project structure they previously used.

Examples:
- You generate a monthly financial report with an excel table and a write up. The tables have the same columns and the you want your write-up document to be formatted the same. Use scaf to make a template of your report folder and instance that template once a month for your next report.
- You have a particular directory structure you like to use when taking a new class. You have a /notes folder, /assignments folder, and /syllabus folder. You could use scaf to instance this directory quickly, anywhere on your machine.

But the best usecase is for programmers (and conveniently skips `.git` folders when creating templates)

Examples:
- You are learning about servers in `go`. You have your basic project structure down for serving an `index` page and have written basic tests. Create a template from your basic server.
- You are have set up a `node` project that interfaces with a database and handles migrations. Create a template from that database, so when you create your next node project that interfaces with a database, you are already started.
- You have a multi-file c++ project with dependencies and some unit tests. You have your makefile working. Create a template from that so your next C++ project will get off the ground faster.


# About the Author - Spring Code Jam

Scaf was made by Karl Miller for the 2023 PennWest California Spring Code Jam for the category "Automate Life".

The prompt:

>  There are many things in our daily lives that are annoying to handle, even only in virtual, such as digging through to find important emails, double checking what appointments were left, checking to see if any missed calls were actually useful. Identify an area of annoyance in your virtual life that could be automated to be made significantly easier and less of a pain to deal with and create a solution for it.

Scaf achieves this by automating the starting up of new digital projects of all kinds and eliminating boilerplate and repetition.

For more detail about the implementation, see the [web documentation](http://www.quaffingcode.com/scaf/html/index.html) or the `reference.pdf` file in this directory.

_Note_: The original project was created in C++. I have switched it to Go because C++ is just a headache to use, and I was having linking issues I didn't feel like trying to resolve.

# Commands

`scaf root { . | subdir }` Registers the root directory for template storage. Makes the current directory or provided subdirectory the root for scaf templates to be saved. This command needs to be used to pick a template directory before scaf's other commands will become functional.

`scaf add { { . | subdir} { alias { infotxt } }}` Create a scaf template from the current directory or subdirectory, and optionally change the name for templating (alias) and add info text. 

`scaf load <template> { subdirectory }` Scaffold one of your templates into the currect directory or the subdirectory if supplied.

`scaf list {filter}` List the available templates. If a filter is provided, it will only list templates with alias matching the filter regex.

`scaf info <template>` Get a description of the given template.

`scaf set <template> <info>` Set the information for a template that can be referenced later.

`scaf remove <template>` Remove a given template.

`scaf rename <template> <newname>` Rename a given template. Info will also be moved over.

`scaf help <command>` Get help about scaf.

## Commands coming soon

Ignores: Right now scaf ignores the .git directory and node_modules directory. Users may want to configure scaf to ignore other directories by default (like bin)
`scaff ignore <regex> ` Add a pattern to the list of ignores
`scaff show ignores` show the list of ignores
`scaff unignore <regex>` unignore a pattern name type

# Getting Scaf

You can get scaf by building it from source, as described in the `Compiling, Installing` section below.

You can also download the binary directly from the project releases.

It is a 64-bit Windows binary. 

# Compiling, Installing

If you are on windows, you can get make with [chocolatey](https://chocolatey.org/), using `choco install make` from an elevated powershell.

Run `make folders` To make the `/bin` and `/obj` folders.

Run `make` to create `bin/scaf.exe`

Run `make test.exe` to create `./test.exe`

Run `test` to run tests.

Run `make clean` to clean the objects, executables, and precompiled headers.

Add the `bin` folder to your system path to access scaf from anywhere on your computer.

Or download the `release` if you are on a 64-bit windows system and add that to the path.

Hint: To add something to your path on windows:
 1. press the windows key
 2. type "path" in the search box
 3. click "edit environment variables"
 4. click the entry that says "path"
 5. click "edit"
 6. click "add"
 7. paste the directory where "scaf.exe" is located

After adding a folder containing "scaf.exe" to your path, you can run scaf from your command-line anywhere using the command `scaf`.

# Example Usage

```
mkdir scafroot
scaf root scafroot                     # registers the root folder for template storage
mkdir my-cpp-proj
cd my-cpp-proj
mkdir obj                              # create some stuff in the folder you are going to templatize
mkdir lib
mkdir src
echo OBDIR = obj > Makefile
scaf add                               # create a scaf template from the current folder
scaf rename my-cpp-proj cpp-basic      # rename a template
scaf set cpp-basic "A basic c++ proj"  # add some info
scaf list c                            # list all templates that start with 'c'
scaf list                              # list all templates
cd ..
mkdir new-proj
scaf load cpp-basic new-proj           # load your template into new-proj
```

# Configuration

`scaf` will populate its own configuration. However, it is possible to manually edit `scaf.conf.json` if desired. This may be useful if you want to add a bunch of 'info' parameters at once, as templates without infos will be listed with empty strings. Shown below is an example configuration object.

```json
{
    "templateDir": "C:\\MyScafs",
    "infos": {
        "js1": "A simple node JS project I set up.",
        "cpp": "c++ with a basic makefile and unit testing framework.",
        "js2": "A webpacked JS front end project.",
        "ts": "A typescript and webpack front end project.",
        "goserv": "A go server."
    }

}
```

`scaf.config.json` will be placed in the same directory where `scaf.exe` is located.

# Dependencies and Credits

- `lib/QUnit.hpp` A lightweight C++ testing framework. [Project Homepage](https://qunit.sourceforge.net/)
- `lib/json.hpp` nlohmann/json's JSON parsing library. [Project Homepage](https://github.com/nlohmann/json)

To compile, you must be using a compiler that supports `-std=c++17`. Scaf uses [filesystem](https://en.cppreference.com/w/cpp/filesystem) for much of its operation.

You also need to support Makefiles. If you are on Windows, you can get make with [chocolatey](https://chocolatey.org/), using `choco install make` from an elevated powershell.

Scaf has not been tested on Linux but was intended to work on Linux. 


