OBDIR = obj
IFLAGS = -I src -I lib -I tests
OBFLAGS = -c -Wall $(IFLAGS)
RM = del /Q /F


bin/scaf.exe: obj/Config.o obj/Template.o lib/json.hpp.gch
	g++ $(IFLAGS) obj/Config.o obj/Template.o src/main.cpp -o bin/scaf

obj/Config.o:
	g++ $(OBFLAGS) -o $(OBDIR)/Config.o src/Config.cpp

# Precompiling the binaries really speeds up complilation process and overall iteration.
lib/json.hpp.gch:
	g++ lib/json.hpp

lib/QUnit.hpp.gch:
	g++ lib/QUnit.hpp

obj/Template.o:
	g++ $(OBFLAGS) -o $(OBDIR)/Template.o src/Template.cpp

obj/TemplateTest.o: obj/Template.o
	g++ $(OBFLAGS) -o $(OBDIR)/TemplateTest.o tests/TemplateTest.cpp

test: obj/TemplateTest.o lib/QUnit.hpp.gch
	g++ $(IFLAGS) obj/TemplateTest.o obj/Template.o tests/testAll.cpp -o test

clean: 
	-$(RM) test.exe
	-$(RM) bin\\scaf.exe
	-$(RM) obj\\*.o
	-$(RM) lib\\*.gch

folders:
	mkdir bin
	mkdir obj
