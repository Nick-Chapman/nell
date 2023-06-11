
units = $(patsubst src/%.c, %, $(wildcard src/*.c))
lls = $(patsubst %, build/%.ll, $(units))

top: build $(lls)

run-%: build/%.ll
	lli $^ 10

build/%.ll: src/%.c Makefile
	clang -Werror -emit-llvm $< -S -o $@

build: ; @mkdir -p $@
