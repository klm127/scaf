OBDIR = obj
IFLAGS = -I src -I lib -I tests -g
OBFLAGS = -c -Wall $(IFLAGS)
RM = del /Q /F


bin/scaf.exe: obj/Config.o obj/Template.o lib/json.hpp.gch
	g++ $(IFLAGS) obj/Config.o obj/Template.o src/main.cpp -o bin/scaf

obj/Config.o: src/Config.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Config.o src/Config.cpp

# Precompiling the binaries really speeds up complilation process and overall iteration.
lib/json.hpp.gch: lib/json.hpp
	g++ lib/json.hpp

lib/QUnit.hpp.gch: lib/QUnit.hpp 
	g++ lib/QUnit.hpp

obj/Template.o: src/Template.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Template.o src/Template.cpp

obj/TemplateTest.o: obj/Template.o tests/TemplateTest.cpp 
	g++ $(OBFLAGS) -o $(OBDIR)/TemplateTest.o tests/TemplateTest.cpp

obj/ConfigTest.o: obj/Config.o tests/ConfigTest.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/ConfigTest.o tests/ConfigTest.cpp

test.exe: obj/TemplateTest.o lib/QUnit.hpp.gch lib/json.hpp.gch obj/ConfigTest.o tests/testAll.cpp
	g++ $(IFLAGS) obj/TemplateTest.o obj/ConfigTest.o obj/Config.o obj/Template.o tests/testAll.cpp -o test

clean: 
	-$(RM) test.exe
	-$(RM) bin\\scaf.exe
	-$(RM) obj\\*.o
	-$(RM) lib\\*.gch

folders:
	mkdir bin
	mkdir obj
