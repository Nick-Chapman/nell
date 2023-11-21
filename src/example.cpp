
#include "example.h"

up<Exp> make_exp() {
  auto e1 = mk<Var>("x1");
  auto e2 = mk<Var>("x2");
  auto e3 = mk<Mul>(mv(e1),mv(e2));
  auto e4 = mk<Num>(1);
  auto e5 = mk<Sub>(mv(e3),mv(e4));
  return e5;
}

up<Def> make_def() { // TODO: two def args
  auto body = make_exp();
  std::vector<Name> formals;
  formals.push_back("x1");
  formals.push_back("x2");
  auto def = mk<Def>("f1",formals,mv(body));
  return def;
}

up<Prog> make_prog() {
  auto def1 = make_def(); // TODO: two defs. one def call another
  std::vector<up<Exp>> args;
  args.push_back(mk<Num>(20));
  args.push_back(mk<Num>(30));
  auto main = mk<Call1>("f1",mv(args));
  auto prog = mk<Prog>(mv(def1),mv(main));
  return prog;
}
