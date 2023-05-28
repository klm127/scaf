package command

import (
	"fmt"
	"os"
	"path"

	"github.com/klm127/scaf/util"
)

// Rename {source template name} {new name}
// Renames a template
func (s *Scaf) Rename(args []string) {
	fail := util.Failer("Rename")
	if len(args) < 2 {
		fail.Msg("Rename requires two arguments; a template to rename, and a name to rename it to.")
	}
	target := args[0]
	rename_to := args[1]
	src_exists, dest_exists := s.config.Has2Dir(target, rename_to)
	if !src_exists {
		fail.Msg("No template with the name " + target + " could be found in your root directory.")
	}
	if dest_exists {
		fmt.Println(rename_to, " is already an existing template. Do you want to remove it?")
		choice := PromptYN(false)
		if choice {
			os.RemoveAll(path.Join(s.config.GetTemplateDirectory(), rename_to))
			fmt.Println("Removed existing template.")
		} else {
			fail.Msg("A template with the name " + rename_to + " already exists.")
		}
	}
	template_dir := s.config.GetTemplateDirectory()
	src_path := path.Join(template_dir, target)
	dest_path := path.Join(template_dir, rename_to)

	err := os.Rename(src_path, dest_path)
	if err != nil {
		fail.Err(err)
	}

	original_info := s.config.GetInfo(target)

	fmt.Println("Renamed template", target, "to", rename_to+".")
	if len(original_info) > 0 {
		s.Set([]string{rename_to, original_info})
	}
}
