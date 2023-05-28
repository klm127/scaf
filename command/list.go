package command

import (
	"fmt"
	"io/fs"
	"os"
	"regexp"

	"github.com/klm127/scaf/util"
)

// Runs the 'list' command, showing available templates if possible, and filtering by an optional regex.
func (s *Scaf) List(args []string) {
	fail := util.Failer("Load")
	if !s.config.HasTemplateDirectory() {
		fail.Msg("No template directory configured. Use 'scaf root' to set a root template directory to save your scaffolds.")
	}

	dirents, err := os.ReadDir(s.config.GetTemplateDirectory())
	if err != nil {
		fail.Err(err)
	}
	if len(args) > 0 {
		s.list_filtered(dirents, args[0])
		return
	}
	// getting the longest helps with pretty printing
	longest := getLongestName(dirents)
	fmt.Println("Listing all available templates: ")
	printListHeader(longest)
	for _, v := range dirents {
		printListLine(longest, v.Name(), s.config.GetInfo(v.Name()))
	}
	fmt.Println("\nLoad command finished.")

}

func (s *Scaf) list_filtered(dirents []fs.DirEntry, filter string) {
	fail := util.Failer("Load")
	match, err := regexp.Compile(filter)
	if err != nil {
		fail.Msg2("You must supply a valid search regex. Try escaping strings by using '\\'.", err)
	}
	filtered := make([]fs.DirEntry, 0, len(dirents))
	for _, v := range dirents {
		if match.Match([]byte(v.Name())) {
			filtered = append(filtered, v)
		}
	}
	longest := getLongestName(filtered)
	fmt.Println("Listing templates matching regex: ", filter)
	printListHeader(longest)
	for _, v := range filtered {
		printListLine(longest, v.Name(), s.config.GetInfo(v.Name()))
	}
}

func printListLine(longest int, name string, info string) {
	fmtLine := fmt.Sprintf("| %%%ds | %%s\n", longest)
	fmt.Printf(fmtLine, name, info)
}

func printListHeader(longest int) {
	line := ""
	for i := 0; i < longest*2; i++ {
		if i%2 == 0 {
			line += " "
		} else {
			line += "-"
		}
	}
	fmter := fmt.Sprintf("\n  %%%ds   %%s\n", longest)
	fmt.Printf(fmter, "Name", "Description")
	fmt.Println(line)
}

func getLongestName(dirents []fs.DirEntry) int {
	longest := 8
	for _, v := range dirents {
		if len(v.Name()) > longest {
			longest = len(v.Name())
		}
	}
	return longest
}
