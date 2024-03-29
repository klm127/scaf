package command

import (
	"fmt"
	"strings"

	"github.com/klm127/scaf/config"
)

/*
Scaf drives the program execution. It loads the config and parses the command line arguments into the correct commands.

Parses and executes the command line arguments.
*/
type Scaf struct {
	config config.Config
}

// NewScaf is the Scaf constructor
func NewScaf() Scaf {
	var scaf Scaf
	scaf.config = config.NewConfig()
	return scaf
}

func (s *Scaf) Start(args []string) {
	if len(args) < 2 {
		s.printHelp()
	} else {
		check := strings.ToLower(args[1])
		switch check {
		case "help":
			s.Help(args[2:])
			break
		case "root":
			s.Root(args[2:])
			s.config.Write()
			break
		case "add":
			s.Add(args[2:])
			s.config.Write()
			break
		case "load":
			s.Load(args[2:])
			break
		case "list":
			s.List(args[2:])
			break
		case "set":
			s.Set(args[2:])
			s.config.Write()
			break
		case "remove":
			s.Remove(args[2:])
			s.config.Write()
			break
		case "ignore":
			s.Ignore(args[2:])
			s.config.Write()
			break
		case "unignore":
			s.UnIgnore(args[2:])
			s.config.Write()
			break
		case "rename":
			s.Rename(args[2:])
			s.config.Write()
			break
		case "show":
			s.Show(args[2:])
			break
		default:
			fmt.Printf("\n'%s' is not a valid scaf command. Run scaf help to see the list of available commands.", check)
		}
	}
}
