package main

import (
	"os"

	"github.com/klm127/scaf/command"
)

func main() {
	args := os.Args
	scaf := command.NewScaf()
	scaf.Start(args)
}
