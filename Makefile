
top: run

run: _build/out.ll
	lli $^ ; echo $$?

see: _build _build/main.exe
	_build/main.exe

_build/out.ll: _build _build/main.exe
	_build/main.exe 2> $@ || rm -f $@

#CPP = g++
CPP = clang++

MAX_ERROR = -Wall -Werror -Wno-mismatched-tags # -Wno-unused-variable

LLVM_FLAGS = \
-DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1 \
-I/home/nic/code/llvm/llvm/include -I/home/nic/code/llvm/build/include \
-std=c++1z
#-fno-exceptions -funwind-tables -fno-rtti -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS

LLVM_LIBS = \
-L/home/nic/code/llvm/build/lib \
-lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMBinaryFormat -lLLVMTargetParser -lLLVMSupport -lLLVMDemangle \
-lrt -ldl -lpthread -lm -lz -ltinfo

units = $(patsubst src/%.cpp, %, $(wildcard src/*.cpp))
objs = $(patsubst %, _build/%.o, $(units))
deps = $(patsubst %, _build/%.d, $(units))

_build/main.exe: $(objs)
	@ echo Linking [$(CPP)]
	@ $(CPP) $^ $(LLVM_LIBS) -o $@

_build/%.o: src/%.cpp
	@ echo Building [$(CPP)] $<
	@ $(CPP) $< $(MAX_ERROR) $(LLVM_FLAGS) -c -o $@ -MMD

_build: ; @mkdir -p $@

-include $(deps)
