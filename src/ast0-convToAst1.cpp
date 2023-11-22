
#include "ast0.h"
#include "misc.h"
#include <vector>

namespace ast0 {

  ast1::Exp& Var::convAst1(ast1::Gen& gen) {
    return gen.var(VarName);
  }
  ast1::Exp& Num::convAst1(ast1::Gen& gen) {
    return gen.num(NumValue);
  }
  ast1::Exp& Mul::convAst1(ast1::Gen& gen) {
    auto& L = MulLeft->convAst1(gen);
    auto& R = MulRight->convAst1(gen);
    return gen.mul(L,R);
  }
  ast1::Exp& Add::convAst1(ast1::Gen& gen) {
    auto& L = AddLeft->convAst1(gen);
    auto& R = AddRight->convAst1(gen);
    return gen.add(L,R);
  }
  ast1::Exp& Sub::convAst1(ast1::Gen& gen) {
    auto& L = SubLeft->convAst1(gen);
    auto& R = SubRight->convAst1(gen);
    return gen.sub(L,R);
  }
  ast1::Exp& LessThan::convAst1(ast1::Gen& gen) {
    auto& L = LessThanLeft->convAst1(gen);
    auto& R = LessThanRight->convAst1(gen);
    return gen.lessThan(L,R);
  }
  ast1::Exp& Ite::convAst1(ast1::Gen& gen) {
    auto& I = IteCond->convAst1(gen);
    auto& T = IteThen->convAst1(gen);
    auto& E = IteElse->convAst1(gen);
    return gen.ite(I,T,E);
  }
  ast1::Exp& Call::convAst1(ast1::Gen& gen) {
    std::vector<ast1::Exp*> args;
    for (auto &exp0 : CallArgs) {
      auto& E = exp0->convAst1(gen);
      args.push_back(&E);
    }
    return gen.call(CallFunc,args);
  }
  ast1::Def& convDef(Def& def0, ast1::Gen& gen) {
    auto& B = def0.DefBody->convAst1(gen);
    return gen.def(def0.DefName,def0.DefFormals,B);
  }
  ast1::Prog& Prog::toAst1(ast1::Gen& gen) {
    std::vector<ast1::Def*> acc;
    for (auto &def0 : ProgDefs) {
      acc.push_back(&convDef(*def0,gen));
    }
    return gen.prog(acc);
  }

}
