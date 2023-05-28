package command

import (
	"fmt"
	"os"
	"path"

	"github.com/klm127/scaf/util"
)

// Removes a template. Remove {templateName}
func (s *Scaf) Remove(args []string) {
	fail := util.Failer("Remove")
	if len(args) < 1 {
		fail.Msg("You must name a template to remove.")
	}
	target := args[0]
	found := s.config.HasDir(target)
	if !found {
		fail.Msg(target + " is not an extant template.")
	}
	err := os.RemoveAll(path.Join(s.config.GetTemplateDirectory(), target))
	if err != nil {
		fail.Err(err)
	}
	fmt.Println("Removed template " + target + ".")

}
