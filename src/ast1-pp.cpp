
#include "ast1-impl.h"
#include "misc.h"

namespace ast1 {

  std::string Var::pp() {
    return VarName;
  }

  std::string Num::pp() {
    return std::to_string(NumValue);
  }

  std::string Mul::pp() {
    return "(" + MulLeft.pp() + " * " + MulRight.pp() + ")";
  }

  std::string Add::pp() {
    return "(" + AddLeft.pp() + " + " + AddRight.pp() + ")";
  }

  std::string Sub::pp() {
    return "(" + SubLeft.pp() + " - " + SubRight.pp() + ")";
  }

  std::string LessThan::pp() {
    return "(" + LessThanLeft.pp() + " < " + LessThanRight.pp() + ")";
  }

  std::string Ite::pp() {
    return "(" + IteCond.pp() + " ? " + IteThen.pp() + " : " + IteElse.pp() + ")";
  }

  std::string ppExps(ExpList& xs) {
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

  std::string Call::pp() {
    return CallFunc + "(" + ppExps(CallArgs) + ")";
  }

  std::string ppNames(NameList& xs) {
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
    return
      "def " + DefName + "(" + ppNames(DefFormals) + "):\n  " +
      DefBody.pp() + ";";
  }

  std::string ppDefs(DefList xs) {
    std::string acc = "";
    bool first = true;
    for (auto &x : xs) {
      if (!first) {
        acc = acc + "\n\n";
      }
      acc = acc + x->pp();
      first = false;
    }
    return acc;
  }

  std::string pp(Prog& prog) {
    return ppDefs(prog.ProgDefs);
  }

}
