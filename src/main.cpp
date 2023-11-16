
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
  int res = exp->eval();
  printf("**res: %d\n", res);
}
