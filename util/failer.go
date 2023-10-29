package util

import (
	"log"
)

type TFailer struct {
	cat string
}

func Failer(name string) TFailer {
	return TFailer{name}
}

func (f *TFailer) Err(err error) {
	f.Msg(err.Error())
}

func (f *TFailer) Msg(msg string) {
	log.Fatalln(f.cat, "failed!\n\tReason: ", msg)
}

func (f *TFailer) Msg2(msg string, err error) {
	f.Msg(msg + "\n\nError: " + err.Error())
}
