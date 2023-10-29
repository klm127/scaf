package command

import (
	"fmt"
	"os"
	"path/filepath"
)

// stringLower not needed

// PromptYN asks a user y/n and defaults to one of them if an invalid response is given.
func PromptYN(default_yn bool) bool {
	fmt.Printf(" y/n? ")
	var response string
	_, err := fmt.Scanln(&response)
	if err != nil {
		if default_yn == true {
			fmt.Println("Error. Defaulting to 'y'")
		} else {
			fmt.Println("Error.Defaulting to 'n'")
		}
		return default_yn
	}
	if response[0] == 'y' || response[0] == 'Y' {
		return true
	}
	if response[0] == 'n' || response[0] == 'N' {
		return false
	}
	if default_yn == true {
		fmt.Println("Error. Defaulting to 'y'")
	} else {
		fmt.Println("Error.Defaulting to 'n'")
	}
	return default_yn
}

// firstArgOrCwd takes the first element of an array and returns it, otherwise, or if the first arg is a '.', it gets the current working directory
func firstArgOrCwd(args []string) (string, error) {
	var target_path string
	var err error
	if len(args) == 0 || args[0] == "." {
		target_path, err = os.Getwd()
		if err != nil {
			return target_path, err
		}
	} else {
		target_path = args[0]
	}
	abs_path, err := filepath.Abs(target_path)
	return abs_path, err

}
