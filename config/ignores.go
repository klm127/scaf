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

	if c.hasIgnore(newIgnore) {
		return errors.New("The ignore string " + newIgnore + " is already being ignored.")
	}

	_, err := regexp.Compile(newIgnore)
	if err != nil {
		return errors.New("That ignore can't be used as a regex. " + err.Error())
	}

	c.data.Ignores = append(c.data.Ignores, newIgnore)
	return nil
}

func (c *Config) hasIgnore(ignore string) bool {
	has := false
	for _, v := range c.data.Ignores {
		if v == ignore {
			return true
		}
	}
	return has
}

func (c *Config) RemoveIgnore(toRemove string) bool {
	newignores := make([]string, 0, len(c.data.Ignores))
	found := false
	for _, v := range c.data.Ignores {
		if v != toRemove {
			newignores = append(newignores, v)
		} else {
			found = true
		}
	}
	c.data.Ignores = newignores
	return found
}
