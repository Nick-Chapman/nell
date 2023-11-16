
#include "ast.h"

int Num::eval() {
  return num;
}

int Sub::eval() {
  auto v1 = left->eval();
  auto v2 = right->eval();
  return v1-v2;
}
