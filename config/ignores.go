package config

import (
	"errors"
	"regexp"
)

// Gets the ignores which were saved in the scaf.json
func (c *Config) GetIgnores() []string {
	return c.data.Ignores
}

// Adds an ignore to the scaf.json. Returns an error if it can't be compiled to a Regex.
func (c *Config) AddIgnore(newIgnore string) error {
	_, err := regexp.Compile(newIgnore)
	if err != nil {
		return errors.New("That ignore can't be used as a regex. " + err.Error())
	}
	c.data.Ignores = append(c.data.Ignores, newIgnore)
	return nil
}
