package main

import (
	"fmt"

	"github.com/klm127/scaf/command"
)

func main() {
	fmt.Printf("ran")
	command.PromptYN(true)
}
