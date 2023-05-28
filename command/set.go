package command

import (
	"fmt"
	"os"

	"github.com/klm127/scaf/util"
)

func (s *Scaf) Set(args []string) {
	fail := util.Failer("Set")
	if len(args) < 2 {
		fail.Msg("Set requires two arguments, the template name and the info text to set it to.")
	}

	targ := args[0]
	info := args[1]

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
	if !exists {
		fmt.Println(targ, "isn't a currently loaded template, but the info will be set for use whenever it is loaded.")
	}
	s.config.SetInfo(targ, info)
	fmt.Println("Set info for ", targ, "to", info)

}
