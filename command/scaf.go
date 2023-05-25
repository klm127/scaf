package command

/*
Scaf drives the program execution. It loads the config and parses the command line arguments into the correct commands.

Parses and executes the command line arguments.
*/
type Scaf struct {
	config int
}

//NewScaf is the Scaf constructor
func NewScaf() Scaf {
	var scaf Scaf
	return scaf
}
