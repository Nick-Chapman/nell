
#include "ast.h"
#include "misc.h"
#include <map>

struct Env { // TODO: class or struct?
  std::map<std::string, Def*> defBinds;
  std::map<std::string, int*> argBinds;
};

int Var::eval(Env& env) {
  auto res = env.argBinds[name];
  if (!res) {
    printf("Var: no binding for: %s\n",name.c_str());
    crash
  }
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
  int A = arg->eval(env);
  Def* D = env.defBinds[func];
  if (!D) {
    printf("Call1: no such function: %s\n",func.c_str());
    crash
  }
  return D->apply(env,A);
}

int Def::apply(Env& env0, int arg) {
  Env env = { env0.defBinds }; // zero the arg binds
  env.argBinds[formal] = &arg;
  auto res = body->eval(env);
  return res;
}

int Prog::eval() {
  Env env;
  env.defBinds[theDef->name] = &(*theDef); // TODO: side-effect ok?
  auto res = main->eval(env);
  return res;
}
