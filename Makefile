CCX64 = x86_64-w64-mingw32-g++
CCX86 = i686-w64-mingw32-g++

CFLAGS = -Os -s

INCLUDE = -Iinclude

SOURCE = src/*.cpp

EXE = build/selfdel.exe

x64:
	mkdir -p build
	$(CCX64) -o $(EXE) $(CFLAGS) $(INCLUDE) $(SOURCE)

x86:
	mkdir -p build
	$(CCX86) -o $(EXE) $(CFLAGS) $(INCLUDE) $(SOURCE)
