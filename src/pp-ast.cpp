
#include "ast.h"
#include "misc.h"
#include <vector>

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

std::string ppExps(std::vector<up<Exp>>& xs) {
  std::string acc = "";
  bool first = true;
  for (auto &x : xs) {
    if (!first) {
      acc = acc + ",";
    }
    acc = acc + x->pp();
    first = false;
  }
  return acc;
}

std::string Call1::pp() {
  return func + "(" + ppExps(args) + ")";
}

std::string ppNames(std::vector<Name> xs) {
  std::string acc = "";
  bool first = true;
  for (auto &x : xs) {
    if (!first) {
      acc = acc + ",";
    }
    acc = acc + x;
    first = false;
  }
  return acc;
}

std::string Def::pp() {
  return "def " + name + "(" + ppNames(formals) + "):\n  " + body->pp() + ";\n\n";
}

std::string Prog::pp() {
  return theDef->pp() + "main: " + main->pp();
}
