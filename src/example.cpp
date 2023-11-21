
#include "example.h"

up<Def> make_square() {
  std::vector<Name> formals;
  formals.push_back("x1");
  return
    mk<Def>("square",formals,
            mk<Mul>(mk<Var>("x1"),mk<Var>("x1")));
}

up<Def> make_f1() {
  std::vector<Name> formals;
  formals.push_back("x1");
  formals.push_back("x2");
  auto body =
    mk<Sub>(mk<Mul>(mk<Var>("x1"),mk<Var>("x2")),
            mk<Num>(1));
  return mk<Def>("f1",formals,mv(body));
}

up<Prog> make_prog() {
  std::vector<up<Def>> defs;
  defs.push_back(make_square());
  defs.push_back(make_f1());
  std::vector<up<Exp>> args;
  args.push_back(mk<Num>(2));
  args.push_back(mk<Num>(3));
  auto main = mk<Call>("f1",mv(args));
  return mk<Prog>(mv(defs),mv(main));
}
