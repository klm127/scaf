package config

import (
	"io/fs"
	"log"
	"os"
	"path/filepath"

	"github.com/klm127/scaf/util"
)

// GetTemplateDirectory returns the template directory that was read from the config file.
func (c *Config) GetTemplateDirectory() string {
	return c.data.TemplateDirectory
}

// Gets dirents for template directory or fails.
func (c *Config) MustGetTemplateDirents() []fs.DirEntry {
	fail := util.Failer("Config")
	if len(c.data.TemplateDirectory) == 0 {
		fail.Msg("No template directory set! Run the command 'root' to set your template directory.")
	}
	dirents, err := os.ReadDir(c.data.TemplateDirectory)
	if err != nil {
		fail.Msg2("No template directory set! Run the command 'root' to set your template directory.", err)
	}
	return dirents
}

// Returns true if directory exists in template directory
func (c *Config) HasDir(name string) bool {
	fail := util.Failer("Config")
	dirents := c.MustGetTemplateDirents()
	for _, dirent := range dirents {
		if dirent.Name() == name {
			if dirent.IsDir() {
				return true
			}
			fail.Msg(name + " is not a directory!")
		}
	}
	return false
}

// Returns whether each directory exists in template directory
func (c *Config) Has2Dir(name1 string, name2 string) (bool, bool) {
	fail := util.Failer("Config")
	exist1 := false
	exist2 := false
	dirents := c.MustGetTemplateDirents()
	for _, dirent := range dirents {
		if dirent.Name() == name1 {
			if dirent.IsDir() {
				exist1 = true
				if exist2 {
					break
				}
			} else {
				fail.Msg(name1 + " is not a directory!")
			}
		} else if dirent.Name() == name2 {
			if dirent.IsDir() {
				exist2 = true
				if exist1 {
					break
				}
			} else {
				fail.Msg(name2 + " is not a directory!")
			}
		}
	}
	return exist1, exist2

}

// SetTemplateDirectory sets a new template directory. Will not be set and an error will be printed if the directory doesn't exist. If the directory is relative, it will be converted to absolute. Returns true if setting was success, false otherwise.
func (c *Config) SetTemplateDirectory(new_dir string) {
	dir, err := filepath.Abs(new_dir)
	if err != nil {
		log.Fatal("Error setting template directory to " + new_dir + " " + err.Error())
	}
	c.data.TemplateDirectory = dir
}

// Checks if a template directory is loaded.
func (c *Config) HasTemplateDirectory() bool {
	if len(c.data.TemplateDirectory) > 0 {
		return true
	}
	return false
}
