
#include <stdio.h>
#include <string>
#include "misc.h"
#include "ast1.h"
#include "example1.h"

// #include "example.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("**expected exactly one arg, got:%d\n",argc-1);
    crash;
  }
  std::string example_name = argv[1];

  ast1::Gen genAst1;

  //auto prog0 = prog_example(example_name);
  //printf("(0)\n%s\n\n", prog0->pp().c_str());
  //int res0 = prog0->eval();
  //printf("(0)evaluation result: %d\n\n", res0);
  //ast0::codegen(*prog0);
  //auto& prog1 = prog0->toAst1(genAst1);

  auto& prog1 = ast1::prog_example(genAst1,example_name);

  //printf("(1)\n%s\n\n", ast1::pp(prog1).c_str());
  //int res1 = ast1::eval(prog1);
  //printf("(1)evaluation result: %d\n\n", res1);

  ast1::codegen(prog1);
}
