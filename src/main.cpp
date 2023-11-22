
#include <stdio.h>
#include <string>
#include "misc.h"
#include "ast1.h"
#include "example1.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("**expected exactly one arg, got:%d\n",argc-1);
    crash;
  }
  std::string example_name = argv[1];
  ast1::Gen genAst1;
  auto& prog1 = ast1::prog_example(genAst1,example_name);
  ast1::codegen(prog1);
}
