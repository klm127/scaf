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
		default:
			fmt.Printf("\n'%s' is not a valid scaf command. Run scaf help to see the list of available commands.", check)
		}
	}
}
