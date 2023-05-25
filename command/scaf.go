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
	result := false
	if len(args) < 2 {
		s.printHelp()
		result = true
	} else {
		check := strings.ToLower(args[1])
		if check == "help" || check == "?" {
			result = s.Help(args[2:])
		}
	}
	if !result {
		fmt.Println(" scaf finished with errors")
	}
}
