package command

import (
	"fmt"
	"os"
	"path"

	"github.com/klm127/scaf/filer"
	"github.com/klm127/scaf/util"
)

func (s *Scaf) Load(args []string) {
	fail := util.Failer("Load")
	if len(args) < 1 {
		fail.Msg("You must specify a template to load.")
	}

	name := args[0]
	templates := s.config.GetTemplateDirectory()
	src := path.Join(templates, name)
	stat, err := os.Stat(src)
	if err != nil {
		fail.Err(err)
	}
	if !stat.IsDir() {
		fail.Msg("Your template " + src + " was a file!")
	}
	s.load2(src, args[1:])
}

func (s *Scaf) load2(src string, args []string) {
	fail := util.Failer("Load")
	dest, err := firstArgOrCwd(args)
	if err != nil {
		fail.Err(err)
	}
	if dest == src {
		fail.Msg("Templates may not load into themselves.")
	}
	result := filer.CopyFolder(src, dest, s.config.GetIgnores())
	result.Print()
	result.PrintErrors()
	fmt.Printf("Load command completed succesfully.")
}
