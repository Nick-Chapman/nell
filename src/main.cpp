
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
  auto exp = make_example();
  //printf("exp: %s\n", exp->pp().c_str());
  //int res = exp->eval();
  //printf("evaluation result: %d\n", res);

  InitializeModule();
  llvm::Value* v = exp->codegen();
  MakeTopLevel(v);
  DumpCode();

}
