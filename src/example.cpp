
#include "example.h"

up<Exp> make_exp() {
  auto e1 = mk<Var>("x1");
  auto e2 = mk<Var>("x1");
  auto e3 = mk<Mul>(mv(e1),mv(e2));
  auto e4 = mk<Num>(1);
  auto e5 = mk<Sub>(mv(e3),mv(e4));
  return e5;
}

up<Def> make_def() {
  auto body = make_exp();
  auto def = mk<Def>("f1","x1",mv(body));
  return def;
}

up<Prog> make_prog() {
  auto def1 = make_def();
  auto ten = mk<Num>(10);
  auto main = mk<Call1>("f1",mv(ten));
  auto prog = mk<Prog>(mv(def1),mv(main));
  return prog;
}
