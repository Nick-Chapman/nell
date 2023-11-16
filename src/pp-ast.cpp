
#include "ast.h"
#include "misc.h"

std::string Num::pp() {
  return std::to_string(num);
}

std::string Sub::pp() {
  return std::string("(") + left->pp() + " - " + right->pp() + ")";
}
