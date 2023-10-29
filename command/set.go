package command

import (
	"fmt"

	"github.com/klm127/scaf/util"
)

// Sets the info, saves in scaf .json
func (s *Scaf) Set(args []string) {
	fail := util.Failer("Set")
	if len(args) < 2 {
		fail.Msg("Set requires two arguments, the template name and the info text to set it to.")
	}

	targ := args[0]
	info := args[1]

	exists := s.config.HasDir(targ)
	if !exists {
		fmt.Println(targ, "isn't a currently loaded template, but the info will be set for use whenever it is loaded.")
	}
	s.config.SetInfo(targ, info)
	fmt.Println("Set info for ", targ, "to", info)

}
