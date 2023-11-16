
#include <stdio.h>
#include <string>
#include <memory>
#include "ast.h"
#include "example.h"

void InitializeModule(); // codegen.cpp
void DumpCode(); // codegen.cpp

int main() {
  printf("**main\n");
  auto exp = make_example();
  printf("exp: %s\n", exp->pp().c_str());
  int res = exp->eval();
  printf("evalualtion result: %d\n", res);
  InitializeModule();
  llvm::Value* code = exp->codegen();
  printf("code gen complete: %p\n", code);
  DumpCode();
}
