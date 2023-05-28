package config

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
)

type configData struct {
	/* Path to the directory holding the templates. Parsed from config file.*/
	TemplateDirectory string

	/* Map to the info strings associated with the templates */
	Infos map[string]string

	/* List of folders to skip and ignore */
	Ignores []string
}

/* Loads a configData, filling it from a file. */
func GetConfigFromFile(a_path string) (*configData, error) {
	loc, err := os.ReadFile(a_path)
	var config_data configData
	config_data.Infos = make(map[string]string)
	config_data.Ignores = make([]string, 0)
	if err != nil {
		if os.IsNotExist(err) {
			fmt.Println("> No config exists at " + a_path + ". Creating.")
			config_data.Ignores = append(config_data.Ignores, "\\.git", "node_modules")
			loc, err = json.Marshal(config_data)
			if err != nil {
				return nil, err
			}
			WriteConfig(a_path, &config_data)
			return &config_data, nil
		}
		return nil, err
	}
	err = json.Unmarshal(loc, &config_data)
	if err != nil {
		return nil, err
	}
	return &config_data, nil
}

func WriteConfig(a_path string, data *configData) {
	marsh, err := json.Marshal(&data)
	if err != nil {
		log.Fatalln("Failed to write config: " + err.Error())
	}
	file, err := os.Create(a_path)
	if err != nil {
		log.Fatalln("Failed to write config: " + err.Error())
	}
	_, err = file.Write(marsh)
	if err != nil {
		log.Fatalln("Failed to write config: " + err.Error())
	}
}

/* Writes the config back, refreshing it. */
func (c *Config) Write() {
	WriteConfig(c.configPath, c.data)
}
