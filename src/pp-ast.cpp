
#include "ast.h"
#include "misc.h"

std::string Var::pp() {
  return name;
}

std::string Num::pp() {
  return std::to_string(num);
}

std::string Sub::pp() {
  return std::string("(") + left->pp() + " - " + right->pp() + ")";
}
