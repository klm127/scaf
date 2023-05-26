package config

/* GetInfo gets info for a given template. Returns empty string if no such info exists. */
func (c *Config) GetInfo(template_name string) string {
	val, ok := c.data.Infos[template_name]
	if !ok {
		return ""
	}
	return val
}

/* SetInfo sets info for a given template. */
func (c *Config) SetInfo(key string, value string) {
	c.data.Infos[key] = value
}
