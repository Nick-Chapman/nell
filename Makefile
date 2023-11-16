
#CPP = g++
CPP = clang++

top: run

build: _build main.exe

run: _build main.exe
	./main.exe

units = $(patsubst src/%.cpp, %, $(wildcard src/*.cpp))
objs = $(patsubst %, _build/%.o, $(units))
deps = $(patsubst %, _build/%.d, $(units))

main.exe: $(objs)
	@ echo Linking [$(CPP)]
	@ $(CPP) $^ -o $@

_build/%.o: src/%.cpp
	@ echo Building [$(CPP)] $<
	@ $(CPP) -Wall -Werror $< -c -o $@ -MMD

_build: ; @mkdir -p $@

-include $(deps)
