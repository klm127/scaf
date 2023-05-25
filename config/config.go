package config

import (
	"log"
	"os"
	"path"
	"path/filepath"
)

const config_file_name = "config.json"

/*
Config provides the functions and classes needed to load scaf's configuration.

When it is constructed, it looks for `scaf.config.json` in the process working directory. If it doesn't exist, it is created. If it is exists as a directory, a runtime error is thrown.

Otherwise, it parses that configuration file to load scaf's saved settings.
*/
type Config struct {
	/* Path to the directory holding the configuration. (Will be the PWD of scaf.exe) */
	configPath string

	/* Data read from the config.json file. */
	data *configData
}

/* NewConfig Initializes the Config. Looks for scaf.config.json in the process working directory. If it doesn't exist, it is created. If it exists as a directory, a runtime error is thrown. */
func NewConfig() Config {
	var config Config
	cpath, err := os.Executable()
	if err != nil {
		log.Fatalf("Couldn't find the executable path; problem with executable directory!" + err.Error())
	}
	abs_path, err := filepath.Abs(filepath.Dir(cpath))
	if err != nil {
		log.Fatalf("Couldn't parse the executable path; problem with executable directory! " + err.Error())
	}
	config.configPath = path.Join(abs_path, config_file_name)
	data, err := GetConfigFromFile(config.configPath)
	if err != nil {
		log.Fatalf("Couldn't parse the config!" + err.Error())
	}
	config.data = data
	return config
}

/* NewConfigFromPath is an alternate constructor. Generally the 0 parameter constructor should be called. Passing a custom configuration is useful for testing purposes.
 */
func NewConfigFromPath(a_path string) Config {
	var config Config
	abs_path, err := filepath.Abs(filepath.Dir(a_path))
	if err != nil {
		log.Fatalf("Couldn't parse the executable path; problem with executable directory! " + err.Error())
	}
	config.configPath = path.Join(abs_path, config_file_name)
	data, err := GetConfigFromFile(config.configPath)
	if err != nil {
		log.Fatalf("Couldn't parse the config!" + err.Error())
	}
	config.data = data
	return config
}
