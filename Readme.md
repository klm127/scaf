# Scaf

Scaf is general purpose, command line, project initialization tool.

Scaf is purpose-agnostic and can be used to start-up ("scaffold") any type of project that has a directory structure.

Scaf works by maintaining directories of templates that the user supplies. When the user wants to scaffold a new project, they may use scaf to copy the contents from one of these directories into their current directory.

# Commands

`scaf root { . | path }` Makes the current directory or _path_ the root for scaf templates to be saved.

`scaf add { subdirectory { infotxt } | . { infotxt } }` Create a scaf template from the current directory or subdirectory. If the current directory is used, and no alias is provided, you will be prompted for a name for your template. If a subdirectory, the subdirectory name will be used. `.git` folders will be ignored.

`scaf <template> { subdirectory }` Scaffold one of your templates into the currect directory or the subdirectory if supplied.

`scaf info <template>` Get a description of the given template.

`scaf set <template> <info>` Set the information for a template that can be referenced later.

`scaf remove <template>` Remove a given template.

`scaf help` Get help about scaf.

