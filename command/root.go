package command

import (
	"errors"
	"fmt"
	"log"
	"os"
)

/* Sets the root directory in the config. Root is the directory where the template folders are located. */
func (s *Scaf) Root(args []string) {
	abs_path, err := firstArgOrCwd(args)
	if err != nil {
		rootFail(err, abs_path)
	}
	stat, err := os.Stat(abs_path)
	if err != nil {
		rootFail(err, abs_path)
	}
	if !stat.IsDir() {
		rootFail(errors.New("Not a directory!"), abs_path)
	}
	s.config.SetTemplateDirectory(abs_path)
	fmt.Printf("Root directory set to: %s\n", s.config.GetTemplateDirectory())
}

func rootFail(err error, a_path string) {
	log.Fatalln("Failed to set root to " + a_path + "! " + err.Error())
}
