
#include "ast.h"
#include "misc.h"
#include <map>

struct Env {
  std::map<std::string, Def*> defBinds;
  std::map<std::string, int*> argBinds;
};

int Var::eval(Env& env) {
  auto res = env.argBinds[VarName];
  if (!res) {
    printf("Var: no binding for: %s\n",VarName.c_str());
    crash
  }
  //printf("lookup: %s=%d\n",name.c_str(),*res);
  return *res;
}

int Num::eval(Env& env) {
  return NumValue;
}

int Mul::eval(Env& env) {
  int L = MulLeft->eval(env);
  int R = MulRight->eval(env);
  return L * R;
}

int Add::eval(Env& env) {
  int L = AddLeft->eval(env);
  int R = AddRight->eval(env);
  return L + R;
}

int Sub::eval(Env& env) {
  int L = SubLeft->eval(env);
  int R = SubRight->eval(env);
  return L - R;
}

int Call::eval(Env& env) {
  Def* D = env.defBinds[CallFunc];
  if (!D) {
    printf("Call: no such function: %s\n",CallFunc.c_str());
    crash
  }
  std::vector<int> AS;
  for (auto &arg : CallArgs) {
    AS.push_back(arg->eval(env));
  }
  return D->apply(env,AS);
}

int Def::apply(Env& env0, std::vector<int> actuals) {
  if (DefFormals.size() != actuals.size()) {
    printf("#formals=%zu, #actuals=%zu\n", DefFormals.size(), actuals.size());
    crash
  }
  Env env = { env0.defBinds }; // zero the arg binds
  for (unsigned i=0; i < DefFormals.size(); i++) {
    //printf("bind: %s=%d\n",formals[i].c_str(),actuals[i]);
    env.argBinds[DefFormals[i]] = &actuals[i];
  }
  return DefBody->eval(env);
}

int Prog::eval() {
  Env env;
  for (auto &def : ProgDefs) {
    env.defBinds[def->DefName] = &(*def);
  }
  auto res = ProgMain->eval(env);
  return res;
}
