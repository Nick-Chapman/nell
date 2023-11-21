
#include "example.h"

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

up<Def> make_fact() {
  std::vector<Name> formals;
  formals.push_back("n");
  std::vector<up<Exp>> nestArgs;
  nestArgs.push_back(mk<Sub>(mk<Var>("n"),mk<Num>(1)));
  auto body =
    mk<Ite>(mk<LessThan>(mk<Var>("n"),mk<Num>(1)),
            mk<Num>(1),
            mk<Mul>(mk<Var>("n"),mk<Call>("fact",mv(nestArgs))));
  return mk<Def>("fact",formals,mv(body));
}

up<Def> make_fib() {
  std::vector<Name> formals;
  formals.push_back("n");
  std::vector<up<Exp>> leftArgs;
  leftArgs.push_back(mk<Sub>(mk<Var>("n"),mk<Num>(1)));
  std::vector<up<Exp>> rightArgs;
  rightArgs.push_back(mk<Sub>(mk<Var>("n"),mk<Num>(2)));
  auto body =
    mk<Ite>(mk<LessThan>(mk<Var>("n"),mk<Num>(2)),
            mk<Var>("n"),
            mk<Add>(mk<Call>("fib",mv(leftArgs)),
                    mk<Call>("fib",mv(rightArgs))));
  return mk<Def>("fib",formals,mv(body));
}

up<Def> make_main() {
  std::vector<Name> formals;
  std::vector<up<Exp>> args;
  args.push_back(mk<Num>(3));
  auto body = mk<Call>("quad",mv(args));
  return mk<Def>("main",formals,mv(body));
}

up<Prog> make_prog() {
  std::vector<up<Def>> defs;
  //defs.push_back(make_absdiff());// works
  defs.push_back(make_square());
  defs.push_back(make_quad());
  defs.push_back(make_main());
  // TODO: compile recursive and foward calls
  //defs.push_back(make_fact());
  //defs.push_back(make_fib());
  return mk<Prog>(mv(defs));
}
