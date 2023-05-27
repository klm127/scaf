package command

import (
	"fmt"
	"io/fs"
	"os"
	"regexp"

	"github.com/klm127/scaf/util"
)

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
	longest := getLongestName(dirents)
	fmt.Println("Available templates: ")
	for _, v := range dirents {
		listLine(longest, v.Name(), s.config.GetInfo(v.Name()))
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
	fmt.Println("Templates matching regex: ", filter)
	for _, v := range filtered {
		listLine(longest, v.Name(), s.config.GetInfo(v.Name()))
	}
}

func listLine(longest int, name string, info string) {
	fmtLine := fmt.Sprintf("| %%%ds | %%s\n", longest)
	fmt.Printf(fmtLine, name, info)
}

func getLongestName(dirents []fs.DirEntry) int {
	longest := 0
	for _, v := range dirents {
		if len(v.Name()) > longest {
			longest = len(v.Name())
		}
	}
	return longest
}
