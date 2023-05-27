package filer

import (
	"fmt"
	"io"
	"os"
	"path"
	"regexp"
	"time"
)

type CopyResult struct {
	from        string
	to          string
	folders     int
	files       int
	time        time.Duration
	bytes       int64
	errors      []string
	skipDetails map[string]int
}

// Adds an error to the copy result
func (result *CopyResult) err(errmsg string) {
	result.errors = append(result.errors, errmsg)
}

func (result *CopyResult) Print() {
	fmt.Println("\n    --* Copy Results *-- ")
	fmt.Println("\n  Copied from: ", result.from)
	fmt.Println("  Copied to:   ", result.to)
	fmt.Println("   - copied", result.folders, "folders.")
	fmt.Println("   - copied", result.files, "files.")
	fmt.Println("   - copied", result.bytes, "bytes.")
	for k := range result.skipDetails {
		fmt.Println("   - skipped", result.skipDetails[k], "instances of", k)
	}
	fmt.Println("   Operation took", result.time)
}

func (result *CopyResult) PrintErrors() {
	if len(result.errors) > 0 {
		fmt.Println("There were", len(result.errors), "errors copying.")
		for _, v := range result.errors {
			fmt.Println(v)
		}

	}
}

func (result *CopyResult) addskip(name string) {
	v, ok := result.skipDetails[name]
	if !ok {
		result.skipDetails[name] = 1
	} else {
		result.skipDetails[name] = v + 1
	}
}

// Copies all contents in from to to, recursively, but skips everything that matches any regex in skipAllmatching
func CopyFolder(from string, to string, skipAllMatching []string) *CopyResult {
	start := time.Now()
	result := CopyResult{from, to, 0, 0, 0, 0, []string{}, make(map[string]int)}
	stat, err := os.Stat(from)
	if err != nil {
		result.err(fmt.Sprintf("Problem checking directory %s. Err: %s", from, err))
		return &result
	}
	if !stat.IsDir() {
		result.err(fmt.Sprintf("%s is not a directory!", from))
		return &result
	}
	invalidator := getInvalidator(skipAllMatching, &result)
	recurseFolder(from, to, invalidator, &result)
	_ = invalidator
	result.time = time.Now().Sub(start)
	return &result
}

// recurses on a folder, copying folders and files that dont match the invalidator
func recurseFolder(from string, to string, Invalidate func(string) bool, result *CopyResult) {
	err := os.MkdirAll(to, os.ModePerm)
	if err != nil {
		result.err(fmt.Sprintf("Failed to make directory %s: Err: %s", to, err.Error()))
		return
	}
	result.folders += 1
	// get the directory entries for that folder
	dirents, err := os.ReadDir(from)
	if err != nil {
		result.err(fmt.Sprintf("Error reading directory %s attempting to copy what entries exist. Err: %s", from, err.Error()))
	}
	// loop through files and folders
	for _, v := range dirents {
		name := v.Name()
		if !Invalidate(v.Name()) {
			if v.IsDir() {
				recurseFolder(path.Join(from, name), path.Join(to, name), Invalidate, result)
			} else {
				copyfile(path.Join(from, name), path.Join(to, name), result)
			}
		} else {
			result.addskip(v.Name())
		}
	}
}

// copys a file or not, adds errors if necessary to the reuslt and updates the count and bytes
func copyfile(from string, to string, result *CopyResult) {
	src, err := os.Open(from)
	if err != nil {
		result.err(fmt.Sprintf("Failed to open file for copying: %s : Err: %s", from, err.Error()))
		return
	}
	dest, err := os.Create(to)
	if err != nil {
		result.err(fmt.Sprintf("Failed to create destination file for copying: %s : Err: %s", to, err.Error()))
		return
	}
	count, err := io.Copy(dest, src)
	if err != nil {
		result.err(fmt.Sprintf("Failed to copy %s to %s : Err : %s", from, to, err))
		return
	}
	result.bytes += count
	result.files += 1
	return
}

// returns a function that checks a string against an array of regular expressions. If any match, returns true. Otherwise, returns false.
func getInvalidator(regstrings []string, result *CopyResult) func(string) bool {
	// convert every string to a regular expression.
	against := make([]*regexp.Regexp, 0, len(regstrings))
	for _, v := range regstrings {
		reg, err := regexp.Compile(v)
		if err != nil {
			result.err(fmt.Sprintf("The ignore string %s was not a valid regular expression. Check your configuration. Skipping.", v))
		} else {
			against = append(against, reg)
		}
	}
	return func(to_check string) bool {
		for _, test := range against {
			if test.Match([]byte(to_check)) {
				return true
			}
		}
		return false
	}
}
