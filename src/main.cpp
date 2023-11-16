
#include <stdio.h>
#include <string>
#include <memory>

#include "ast.h"
#include "example.h"

/*void panic(const std::string& mes) {
  printf("**panic %s\n", mes.c_str());
  fflush(stdout);
  abort();
}*/

int main() {
  printf("**main\n");
  auto exp = make_example();
  printf("exp: %s\n", exp->pp().c_str());
  int res = exp->eval();
  printf("evalualtion result: %d\n", res);
}
