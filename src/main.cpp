
#include <stdio.h>
#include <string>
#include <memory>
#include "ast0.h"
#include "misc.h"
#include "example.h"
#include "codegen.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("**expected exactly one arg, got:%d\n",argc-1);
    crash;
  }
  std::string example_name = argv[1];
  auto prog = prog_example(example_name);
  //printf("\n%s\n\n", prog->pp().c_str());
  //int res = prog->eval();
  //printf("evaluation result: %d\n\n", res);
  codegen(*prog);
}
