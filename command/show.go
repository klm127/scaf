package command

import (
	"fmt"
	"strings"

	"github.com/klm127/scaf/util"
)

func (s *Scaf) Show(args []string) {
	fail := util.Failer("Show")
	if len(args) < 1 {
		fail.Msg("Show what?")
	}
	arg := strings.ToLower(args[0])
	if arg == "list" || arg == "template" || arg == "templates" {
		s.List(args[1:])
		return
	}
	if arg == "ignores" {
		s.ShowIgnores()
		return
	}
	fail.Msg("I can't show " + arg + "; I don't know that is.")
}

func (s *Scaf) ShowIgnores() {
	fmt.Println("Any file or folder matching these patterns is ignored when scaf copies: ")
	ignores := s.config.GetIgnores()
	if len(ignores) < 1 {
		fmt.Println("There are no patterns being ignored.")
		return
	}
	fmt.Println()
	for _, v := range ignores {
		fmt.Println(v)
	}
}
