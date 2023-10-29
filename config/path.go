package config

// GetPath gets the path that was loaded at the time of the configs construction.
func (c *Config) GetPath() string {
	return c.configPath
}
