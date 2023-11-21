
units = $(patsubst src/%.c, %, $(wildcard src/*.c))
lls = $(patsubst %, build/%.ll, $(units))

top: build $(lls)

run-%: build/%.ll
	lli $^

build/%.ll: src/%.c Makefile
	clang -O3 -Werror -emit-llvm $< -S -o $@

build: ; @mkdir -p $@
