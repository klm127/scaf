package config

/*
   Config provides the functions and classes needed to load scaf's configuration.

   When it is constructed, it looks for `scaf.config.json` in the process working directory. If it doesn't exist, it is created. If it is exists as a directory, a runtime error is thrown.

   Otherwise, it parses that configuration file to load scaf's saved settings.
*/
type Config struct {
	/* Path to the directory holding the configuration. (Will be the PWD of scaf.exe) */
	configPath string
	/* Path to the directory holding the templates. Parsed from config file.*/
	templateDirectory string
	/* A map of the info strings associated with templates. Parsed from config file. */
	infos map[string]string
}

/* NewConfig Initializes the Config. Looks for scaf.config.json in the process working directory. If it doesn't exist, it is created. If it exists as a directory, a runtime error is thrown. */
func NewConfig() Config {
	var config Config
	return config
}

/* NewConfigFromPath is an alternate constructor. Generally the 0 parameter constructor should be called. Passing a custom configuration is useful for testing purposes.
 */
func NewConfigFromPath(path string) Config {
	var config Config
	return config
}
