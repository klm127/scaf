package command

import (
	"fmt"
	"strings"
)

/* Help dispatches the help command by calling the appropriate printing function depending on the next arg. */
func (s *Scaf) Help(args []string) {
	if len(args) == 0 {
		s.printHelp()
		return
	}
	check := strings.ToLower(args[0])
	if check == "root" {
		printHelpRoot()
	} else if check == "add" {
		printHelpAdd()
	} else if check == "info" {
		printHelpInfo()
	} else if check == "set" {
		printHelpSet()
	} else if check == "remove" {
		printHelpRemove()
	} else if check == "load" {
		printHelpLoad()
	} else if check == "rename" {
		printHelpRename()
	} else if check == "list" {
		printHelpList()
	} else {
		fmt.Println(" I don't have help on that topic. ")
	}
}

/* printCommandName pretty prints a string with a box around it, centered. */
func printCommandName(s string) {
	space := ""
	for i := 0; i < 10; i++ {
		space += " "
	}
	bar := ""
	for i := 0; i < 16; i++ {
		bar += "-"
	}
	n_half := (16 - 2 - len(s)) / 2
	half := ""
	for i := 0; i < n_half; i++ {
		half += " "
	}
	fmt.Println("\n" + space + bar)
	fmt.Println(space + "|" + half + s + half + "|")
	fmt.Println(space + bar + "\n")
}

/* printHelp prints overall program help. Occurs if no arguments, 'help', or '?' are passed. */
func (s *Scaf) printHelp() {
	printCommandName("help")
	fmt.Println(" scaf is a command line utility for quickly scaffolding any type of project.")
	fmt.Println(" It enables you to save project templates (scaffolds) in a special folder on your hard drive.")
	fmt.Println(" When you want to create a project using one of these templates, scaf will copy the contents")
	fmt.Println(" of the template into the folder you want to scaffold.")
	fmt.Println("\n     Commands:  root, add, load, list, info, set, remove, rename")
	if !s.config.HasTemplateDirectory() {
		fmt.Println("\n Warning: You do not currently have a template directory loaded.")
		fmt.Println(" To use scaf, you must first set a template directory with the root command. ")
	} else {
		fmt.Printf("\nYour template directory is currently set to: %s", s.config.GetTemplateDirectory())
	}
	fmt.Println("\n Use scaf help <command> for more information about a specific command.")
}

/* printHelpRoot prints help for the root command. */
func printHelpRoot() {
	printCommandName("root")
	fmt.Println("Scaf: Help for the root command:")
	fmt.Println("\n\tSyntax: scaf root { . | subdir }")
	fmt.Println("\nRegisters the root template directory. This is where your templates will be saved.")
	fmt.Println("If no subdir is provided, scaf will use the current directory as the root.")
}

/* printHelpAdd prints help for the add command. */
func printHelpAdd() {
	printCommandName("add")
	fmt.Println("Scaf: Help for the add command:")
	fmt.Println("\n\tSyntax: scaf add { { . | subdir} { alias { infotxt } }}")
	fmt.Println("\nCreates a template from the current directory or a subdirectory.")
	fmt.Println("If a subdirectory is provided, you may also provide an alias.")
	fmt.Println("If an alias is provided, you may also provide info text.")
	fmt.Println("If no alias is provided, the template will be named after the first word in the directory.")
	fmt.Println("If no subdir is provided, scaf will create a template from the current directory.")
}

/* printHelpInfo prints help for the info command. */
func printHelpInfo() {
	printCommandName("info")
	fmt.Println("Scaf: Help for the info command:")
	fmt.Println("\nSyntax: scaf info <template>")
	fmt.Println("\nPrints info for a template.")
	fmt.Println("Info is a string that you have previously set with the set command.")
	fmt.Println("It's useful for remembering what a template is.")
}

/* printHelpSet prints help for the set command. */
func printHelpSet() {
	printCommandName("set")
	fmt.Println("Scaf: Help for the set command:")
	fmt.Println("\n\tSyntax: scaf set <template> { infotext }")
	fmt.Println("\nSets the info text for a template.")
	fmt.Println("You can check this info later with the info command.")
	fmt.Println("It's useful for remembering what a template is.")
}

/* printHelpRemove prints help for the remove command. */
func printHelpRemove() {
	printCommandName("remove")
	fmt.Println("Scaf: Help for the remove command:")
	fmt.Println("\n\tSyntax: scaf remove <template>")
	fmt.Println("\nRemoves a template from your root.")
	fmt.Println("Use this when a template has outlived its usefulness.")
}

/* printHelpLoad prints help for the load command. */
func printHelpLoad() {
	printCommandName("load")
	fmt.Println("Scaf: Help for the load command:")
	fmt.Println("\n\tSyntax: scaf load <template> { . | subdir }")
	fmt.Println("\nLoads a template named <template> from your root.")
	fmt.Println("Copies all files and folders in <template> into the given directory.")
	fmt.Println("Use load to load up a scaffold.")
}

/* printHelpRename prints help for the rename command. */
func printHelpRename() {
	printCommandName("rename")
	fmt.Println("Scaf: Help for the rename command:")
	fmt.Println("\n\tSyntax: scaf rename <template> <newname> ")
	fmt.Println("\nRenames a template.")
}

/* printHelpList prints help for the list command. */
func printHelpList() {
	printCommandName("list")
	fmt.Println("Scaf: Help for the list command:")
	fmt.Println("\n\tSyntax: scaf list { filter }")
	fmt.Println("\nLists all available templates.")
	fmt.Println("If filter is provided, only lists those that start with filter.")
}

// add ignores
// list ignores
// remove ignores
