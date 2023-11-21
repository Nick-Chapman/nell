
#include <stdio.h>
#include <string>
#include <memory>
#include "ast.h"
#include "example.h"
#include "codegen.h"

int main() {

  auto prog = make_prog();

  printf("\n%s\n\n", prog->pp().c_str());
  int res = prog->eval();
  printf("evaluation result: %d\n\n", res);

  codegen(*prog);
  // TODO: control constant folding?
  // TODO JIT compile and execute

}
