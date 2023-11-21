
#include "ast.h"
#include "misc.h"
#include <map>

struct Env {
  std::map<std::string, Def*> defBinds;
  std::map<std::string, int*> argBinds;
};

int Var::eval(Env& env) {
  auto res = env.argBinds[name];
  if (!res) {
    printf("Var: no binding for: %s\n",name.c_str());
    crash
  }
  //printf("lookup: %s=%d\n",name.c_str(),*res);
  return *res;
}

int Num::eval(Env& env) {
  return num;
}

int Mul::eval(Env& env) {
  int L = left->eval(env);
  int R = right->eval(env);
  return L * R;
}

int Sub::eval(Env& env) {
  int L = left->eval(env);
  int R = right->eval(env);
  return L - R;
}

int Call1::eval(Env& env) {
  Def* D = env.defBinds[func];
  if (!D) {
    printf("Call1: no such function: %s\n",func.c_str());
    crash
  }
  std::vector<int> AS;
  for (auto &arg : args) {
    AS.push_back(arg->eval(env));
  }
  return D->apply(env,AS);
}

int Def::apply(Env& env0, std::vector<int> actuals) {
  if (formals.size() != actuals.size()) {
    printf("#formals=%zu, #actuals=%zu\n", formals.size(), actuals.size());
    crash
  }
  Env env = { env0.defBinds }; // zero the arg binds
  for (unsigned i=0; i < formals.size(); i++) {
    //printf("bind: %s=%d\n",formals[i].c_str(),actuals[i]);
    env.argBinds[formals[i]] = &actuals[i];
  }
  return body->eval(env);
}

int Prog::eval() {
  Env env;
  env.defBinds[theDef->name] = &(*theDef);
  auto res = main->eval(env);
  return res;
}
