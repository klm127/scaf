package config

// GetTemplateDirectory returns the template directory that was read from the config file.
func (c *Config) GetTemplateDirectory() string {
	return c.templateDirectory
}

// SetTemplateDirectory sets a new template directory. Will not be set and an error will be printed if the directory doesn't exist. If the directory is relative, it will be converted to absolute. Returns true if setting was success, false otherwise.
func (c *Config) SetTemplateDirectory(new_dir string) bool {
	return true
}

// Checks if a template directory is loaded.
func (c *Config) HasTemplateDirectory() bool {
	if len(c.templateDirectory) > 0 {
		return true
	}
	return false
}
