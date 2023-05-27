package command

import (
	"errors"
	"fmt"
	"log"
	"os"
	"path"
	"path/filepath"

	"github.com/klm127/scaf/filer"
)

// Adds a directory as a template by copying it to the template folder.
func (s *Scaf) Add(args []string) {
	// target (being copied from) is first argument, defaulting to "."
	abs_path, err := firstArgOrCwd(args)
	if err != nil {
		AddFail(err)
	}
	// target must be a directory and exist
	stat, err := os.Stat(abs_path)
	if err != nil {
		AddFail(err)
	}
	if !stat.IsDir() {
		AddFail(errors.New(abs_path + " is not a directory!"))
	}
	// the name of the template will be the name of the folder, unless an optional alias 2nd argument is supplied
	var alias string
	if len(args) > 1 {
		alias = args[1]
	} else {
		alias = filepath.Base(abs_path)
	}

	template_dir := s.config.GetTemplateDirectory()

	// prevent breaking of program
	copy_to_loc := path.Join(template_dir, alias)
	if abs_path == template_dir {
		AddFail(errors.New("You can't copy the root directory into itself!"))
	}

	// if an alias already exists, you have the option to delete it, defaulting to don't delete.
	exists := filer.DirExists(template_dir, alias)
	if exists {
		fmt.Println("A template named " + alias + " already exists. Would you like to delete it? ")
		delete := PromptYN(false)
		if !delete {
			AddFail(errors.New("A template name " + alias + "already exists."))
		}
		err = os.RemoveAll(path.Join(template_dir, alias))
		if err != nil {
			AddFail(errors.New("Failed to remove " + alias + " from " + template_dir + "!" + err.Error()))
		}
		fmt.Println("Removed old template '", alias+"'.")
	}
	// if an info parameter is supplied, thats set in the config for later saving to scaf.json
	if len(args) > 2 {
		s.config.SetInfo(alias, args[2])
	}

	// copy the folder, print the rrors
	result := filer.CopyFolder(abs_path, copy_to_loc, s.config.GetIgnores())
	result.Print()
	result.PrintErrors()
	_, err = os.Stat(copy_to_loc)
	// Failure if directory isn't created
	if err != nil {
		AddFail(errors.New("Failed to read stats of final output directory."))
	}
	fmt.Println("Add completed succesfully.")
}

// get the add directory
// recursively copy through the entire directory
// on all levels, skip files and folders that match the "ignore" setting

func AddFail(err error) {
	log.Fatalln("Failed to process Add command: " + err.Error())
}
