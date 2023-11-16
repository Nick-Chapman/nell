# nell

Explore LLVM.

#### Getting started
- [Getting started with LLVM](https://www.cs.utexas.edu/~pingali/CS380C/2019/assignments/llvm-guide.html)
- [Getting Started with the LLVM System](https://llvm.org/docs/GettingStarted.html)

#### Some prerequisites
```
sudo apt install ninja-build
sudo apt install clang
```

#### Clone llvm-project
```
cd ~/code
git clone https://github.com/llvm/llvm-project.git llvm
cd llvm
```

#### Getting the latest cmake
```
sudo apt remove --purge cmake
sudo snap install cmake --classic
```

#### Configure and build llvm
```
cmake -S llvm -B build -G Ninja -DLLVM_TARGETS_TO_BUILD=host -DCMAKE_BUILD_TYPE=MinSizeRel
cd build
ninja
```

### Early play

- [play1](play1) Compile C code using clang to LLVM.
- [play2](play2) Generate LLVM by hand using Haskell.
