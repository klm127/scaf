package command

import (
	"fmt"
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
