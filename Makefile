OBDIR = obj
IFLAGS = -I src -I lib -I tests
OBFLAGS = -c -Wall $(IFLAGS)
RM = del /Q /F


bin/scaf.exe: obj/Config.o obj/Template.o
	g++ $(IFLAGS) obj/Config.o obj/Template.o src/json.hpp src/main.cpp -o bin/scaf

obj/Config.o:
	g++ $(OBFLAGS) -o $(OBDIR)/Config.o src/Config.cpp

obj/Template.o:
	g++ $(OBFLAGS) -o $(OBDIR)/Template.o src/Template.cpp

obj/TemplateTest.o: obj/Template.o
	g++ $(OBFLAGS) -o $(OBDIR)/TemplateTest.o tests/TemplateTest.cpp

test: obj/TemplateTest.o
	g++ $(IFLAGS) obj/TemplateTest.o obj/Template.o tests/QUnit.hpp tests/testAll.cpp -o test

clean: 
	-$(RM) test.exe
	-$(RM) bin\\scaf.exe
	-$(RM) obj\\*.o
	-$(RM) tests\\*.gch

folders:
	mkdir bin
	mkdir obj
