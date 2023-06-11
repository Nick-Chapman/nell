
top: gen/fib.ll
	lli $^ || echo $$?

exe = .stack-work/dist/x86_64-linux/Cabal-3.6.3.0/build/main.exe/main.exe

$(exe): src/*.hs
	stack build
	touch $(exe)

gen/fib.ll: $(exe)
	$(exe)
