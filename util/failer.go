package util

import (
	"log"
)

type failer_struct struct {
	cat string
}

func Failer(name string) failer_struct {
	return failer_struct{name}
}

func (f *failer_struct) Err(err error) {
	f.Msg(err.Error())
}

func (f *failer_struct) Msg(msg string) {
	log.Fatalln(f.cat, "failed!\n\tReason: ", msg)
}

func (f *failer_struct) Msg2(msg string, err error) {
	f.Msg(msg + "\n\nError: " + err.Error())
}
