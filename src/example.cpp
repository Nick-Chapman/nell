
#include "example.h"

// TODO: recursion: fib, fact

up<Def> make_absdiff() {
  std::vector<Name> formals;
  formals.push_back("x");
  formals.push_back("y");
  auto body = mk<Ite>(mk<LessThan>(mk<Var>("x"),mk<Var>("y")),
                      mk<Sub>(mk<Var>("y"),mk<Var>("x")),
                      mk<Sub>(mk<Var>("x"),mk<Var>("y")));
  return mk<Def>("absdiff",formals,mv(body));
}

up<Def> make_square() {
  std::vector<Name> formals;
  formals.push_back("x");
  return
    mk<Def>("square",formals,
            mk<Mul>(mk<Var>("x"),mk<Var>("x")));
}

up<Def> make_quad() {
  std::vector<Name> formals;
  formals.push_back("x");
  std::vector<up<Exp>> innerArgs;
  innerArgs.push_back(mk<Var>("x"));
  auto inner = mk<Call>("square",mv(innerArgs));
  std::vector<up<Exp>> outerArgs;
  outerArgs.push_back(mv(inner));
  auto outer = mk<Call>("square",mv(outerArgs));
  return mk<Def>("quad",formals,mv(outer));
}

up<Def> make_f1() {
  std::vector<Name> formals;
  formals.push_back("x");
  formals.push_back("y");

  std::vector<up<Exp>> args;
  args.push_back(mk<Var>("y"));
  auto e = mk<Call>("square",mv(args));

  auto body =
    mk<Sub>(mk<Add>(mk<Var>("x"),mv(e)),
            mk<Num>(1));
  return mk<Def>("f1",formals,mv(body));
}

up<Prog> make_prog() {
  std::vector<up<Def>> defs;
  defs.push_back(make_absdiff());
  defs.push_back(make_square());
  defs.push_back(make_quad());
  defs.push_back(make_f1());
  std::vector<up<Exp>> args;
  args.push_back(mk<Num>(3));
  auto main = mk<Call>("quad",mv(args));
  return mk<Prog>(mv(defs),mv(main));
}
