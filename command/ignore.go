package command

import (
	"fmt"

	"github.com/klm127/scaf/util"
)

// add a string regex to the ignore list
func (s *Scaf) Ignore(args []string) {
	fail := util.Failer("Ignore")
	if len(args) < 1 {
		fail.Msg("Ignore requires an argument.")
	}
	s.config.AddIgnore(args[0])
}

// remove something from the ignore list
func (s *Scaf) UnIgnore(args []string) {
	fail := util.Failer("UnIgnore")
	if len(args) < 1 {
		fail.Msg("Unignore requires an argument.")
	}
	found := s.config.RemoveIgnore(args[0])
	if !found {
		fail.Msg("Couldn't find the string " + args[0] + " in the list of ignores.")
	}
	fmt.Println("Removed the ignore string: " + args[0] + ".")
}
