
#include "ast1-impl.h"
#include "misc.h"

namespace ast1 {

  Gen::~Gen() {
    for (auto &exp : Exps) {
      //printf("delete-exp: %p\n",exp);
      delete exp;
    }
    for (auto &def : Defs) {
      //printf("delete-def: %p\n",def);
      delete def;
    }
    for (auto &prog : Progs) {
      //printf("delete-prog: %p\n",prog);
      delete prog;
    }
  }

  Exp& Gen::num(int value) {
    auto x = new Num(value);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::var(Name name) {
    auto x = new Var(name);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::mul(Exp& left,Exp& right) {
    auto x = new Mul(left,right);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::add(Exp& left,Exp& right) {
    auto x = new Add(left,right);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::sub(Exp& left,Exp& right) {
    auto x = new Sub(left,right);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::lessThan(Exp& left,Exp& right) {
    auto x = new LessThan(left,right);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::ite(Exp& I,Exp& T,Exp& E) {
    auto x = new Ite(I,T,E);
    Exps.push_back(x);
    return *x;
  }

  Exp& Gen::call(Name func,ExpList args) {
    auto x = new Call(func,args);
    Exps.push_back(x);
    return *x;
  }

  Def& Gen::def(Name name,NameList formals,Exp& body) {
    auto x = new Def(name,formals,body);
    Defs.push_back(x);
    return *x;
  }

  Prog& Gen::prog(DefList defs) {
    auto x = new Prog(defs);
    Progs.push_back(x);
    return *x;
  }

}
