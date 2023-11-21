
#include "ast.h"
#include "misc.h"

std::string Var::pp() {
  return name;
}

std::string Num::pp() {
  return std::to_string(num);
}

std::string Mul::pp() {
  return "(" + left->pp() + " * " + right->pp() + ")";
}

std::string Sub::pp() {
  return "(" + left->pp() + " - " + right->pp() + ")";
}

std::string Call1::pp() {
  return func + "(" + arg->pp() + ")";
}

std::string Def::pp() {
  return "def " + name + "(" + formal + "):\n  " + body->pp() + ";\n\n";
}

std::string Prog::pp() {
  return theDef->pp() + "main: " + main->pp();
}
