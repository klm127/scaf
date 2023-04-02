OBDIR = obj
IFLAGS = -I src -I lib -I tests -g
OBFLAGS = -Wall -Wno-unknown-pragmas $(IFLAGS) -std=c++17 -c
RM = del /Q /F


bin/scaf.exe: $(OBDIR)/Config.obj $(OBDIR)/Template.obj $(OBDIR)/Scaf.obj $(OBDIR)/Filer.obj lib/json.hpp.gch src/main.cpp
	g++ $(IFLAGS) $(OBDIR)/Config.obj $(OBDIR)/Template.obj $(OBDIR)/Scaf.obj $(OBDIR)/Filer.obj src/main.cpp -o bin/scaf

obj/Config.obj: src/Config.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Config.obj src/Config.cpp

# Precompiling the binaries really speeds up complilation process and overall iteration.
lib/json.hpp.gch: lib/json.hpp
	g++ lib/json.hpp

lib/QUnit.hpp.gch: lib/QUnit.hpp 
	g++ lib/QUnit.hpp

obj/Scaf.obj: src/Scaf.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Scaf.obj src/Scaf.cpp

obj/Filer.obj: src/Filer.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Filer.obj src/Filer.cpp

obj/Template.obj: src/Template.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/Template.obj src/Template.cpp

obj/TemplateTest.obj: $(OBDIR)/Template.obj tests/TemplateTest.cpp 
	g++ $(OBFLAGS) -o $(OBDIR)/TemplateTest.obj tests/TemplateTest.cpp

obj/FilerTest.obj: $(OBDIR)/Filer.obj tests/FilerTest.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/FilerTest.obj tests/FilerTest.cpp

obj/ConfigTest.obj: $(OBDIR)/Config.obj tests/ConfigTest.cpp
	g++ $(OBFLAGS) -o $(OBDIR)/ConfigTest.obj tests/ConfigTest.cpp

test.exe: $(OBDIR)/TemplateTest.obj lib/QUnit.hpp.gch lib/json.hpp.gch $(OBDIR)/ConfigTest.obj $(OBDIR)/FilerTest.obj tests/testAll.cpp
	g++ $(IFLAGS) $(OBDIR)/TemplateTest.obj $(OBDIR)/ConfigTest.obj $(OBDIR)/Config.obj $(OBDIR)/Filer.obj $(OBDIR)/FilerTest.obj $(OBDIR)/Template.obj tests/testAll.cpp -o test

clean: 
	-$(RM) test.exe
	-$(RM) bin\\scaf.exe
	-$(RM) obj\\*.obj
	-$(RM) lib\\*.gch
	-$(RM) docs\\latex

clean_docs:
	-$(RM) reference.pdf
	rmdir docs /s /q

folders:
	mkdir bin
	mkdir obj

docs/html/index.html: tests/*.cpp src/*.cpp src/*.h
	doxygen

docs/latex/refman.pdf: docs/html/index.html
	cd docs/latex && make.bat

reference.pdf: docs/latex/refman.pdf
	copy ".\docs\latex\refman.pdf" ".\reference.pdf"
