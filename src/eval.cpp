
#include "ast.h"
#include "misc.h"

int Var::eval() {
  //TODO: Need environment for bindings from var->value
  // Inthe meantime, hardcode(hack) vars I need.
  if (name == "xx1") {
    return 10045;
  }
  if (name == "xx2") {
    return 105;
  }
  crash
}

int Num::eval() {
  return num;
}

int Sub::eval() {
  auto v1 = left->eval();
  auto v2 = right->eval();
  return v1-v2;
}
