build:
	g++ -o bin/scaf -Wall -I src src/main.cpp src/Template.cpp src/Config.cpp

run:
	bin/scaf

build_tests:
	g++ -o test -Wall -I src src/Template.cpp tests/Qunit.hpp tests/testAll.cpp tests/TemplateTest.cpp

test:
	tests




