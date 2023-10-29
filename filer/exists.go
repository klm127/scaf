package filer

import (
	"log"
	"os"
)

func DirExists(parentdir string, name string) bool {
	dirents, err := os.ReadDir(parentdir)
	if err != nil {
		log.Fatalln("Failed to handle directory entries." + err.Error())
	}
	for _, v := range dirents {
		if v.IsDir() {
			if v.Name() == name {
				return true
			}
		}
	}
	return false
}

func ReplaceDir(parentdir string, subdir_to_replace string, dir_to_replace_with string) {

}
