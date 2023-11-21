
#include <stdio.h>
#include <string>
#include <memory>
#include "ast.h"
#include "example.h"

void InitializeModule(); // codegen.cpp
void DumpCode(); // codegen.cpp
void MakeTopLevel(llvm::Value*); // codegen.cpp

int main() {
  printf("**main\n");

  auto prog = make_prog();
  printf("prog: %s\n", prog->pp().c_str());

  int res = prog->eval();
  printf("evaluation result: %d\n", res);

  //InitializeModule();
  //llvm::Value* v = exp->codegen();
  //MakeTopLevel(v);
  // TODO: control constant folding?
  //DumpCode();
  // TODO write llvm code to file, for external compilation & execution
  // TODO JIT compile and execute
}
