OBDIR = obj
IFLAGS = -I src -I lib -I tests -g
OBFLAGS = -Wall -Wno-unknown-pragmas $(IFLAGS) -std=c++17 -c
RM = del /Q /F


bin/scaf.exe: obj/Config.obj obj/Template.obj obj/Scaf.obj lib/json.hpp.gch
	g++ $(IFLAGS) $(OBDIR)/Config.obj $(OBDIR)/Template.obj $(OBDIR)/Scaf.obj src/main.cpp -o bin/scaf

obj/Config.obj: src/Config.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Config.obj src/Config.cpp

# Precompiling the binaries really speeds up complilation process and overall iteration.
lib/json.hpp.gch: lib/json.hpp
	g++ lib/json.hpp

lib/QUnit.hpp.gch: lib/QUnit.hpp 
	g++ lib/QUnit.hpp

obj/Scaf.obj: src/Scaf.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Scaf.obj src/Scaf.cpp

obj/Template.obj: src/Template.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Template.obj src/Template.cpp

obj/TemplateTest.obj: obj/Template.obj tests/TemplateTest.cpp 
	g++ $(OBFLAGS) -o $(OBDIR)/TemplateTest.obj tests/TemplateTest.cpp

obj/ConfigTest.obj: obj/Config.o tests/ConfigTest.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/ConfigTest.obj tests/ConfigTest.cpp

test.exe: $(OBDIR)/TemplateTest.obj lib/QUnit.hpp.gch lib/json.hpp.gch $(OBDIR)/ConfigTest.obj tests/testAll.cpp
	g++ $(IFLAGS) $(OBDIR)/TemplateTest.obj $(OBDIR)/ConfigTest.obj $(OBDIR)/Config.obj $(OBDIR)/Template.obj tests/testAll.cpp -o test

clean: 
	-$(RM) test.exe
	-$(RM) bin\\scaf.exe
	-$(RM) obj\\*.obj
	-$(RM) lib\\*.gch

folders:
	mkdir bin
	mkdir obj
