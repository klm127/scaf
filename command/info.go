package command

import (
	"fmt"
	"os"

	"github.com/klm127/scaf/util"
)

func (s *Scaf) Info(args []string) {
	fail := util.Failer("Info")
	if len(args) < 1 {
		fail.Msg("You must supply a template.")
	}
	targ := args[0]
	dirents, err := os.ReadDir(s.config.GetTemplateDirectory())
	if err != nil {
		fail.Err(err)
	}
	exists := false
	for _, dirent := range dirents {
		if dirent.Name() == targ {
			exists = true
			break
		}
	}
	data := s.config.GetInfo(targ)
	if len(data) == 0 {
		if exists {
			fmt.Println("There is no info for template", targ+".")
		} else {
			fmt.Println("Template", targ, "does not exist.")
		}
	} else {
		if !exists {
			fmt.Println("Template", targ, "doesn't exist in root, but there is info that exists for when it is added or root is changed.")
		}
		fmt.Println("Info for ", targ, ": ", data)
	}

}
