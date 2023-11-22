
#include "example.h"
#include "misc.h"

using namespace ast;

up<Def> def_absdiff() {
  std::vector<Name> formals;
  formals.push_back("x");
  formals.push_back("y");
  auto body = mk<Ite>(mk<LessThan>(mk<Var>("x"),mk<Var>("y")),
                      mk<Sub>(mk<Var>("y"),mk<Var>("x")),
                      mk<Sub>(mk<Var>("x"),mk<Var>("y")));
  return mk<Def>("absdiff",formals,mv(body));
}

up<Def> def_square() {
  std::vector<Name> formals;
  formals.push_back("x");
  return
    mk<Def>("square",formals,
            mk<Mul>(mk<Var>("x"),mk<Var>("x")));
}

up<Def> def_quad() {
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

up<Def> def_fact() {
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

up<Def> def_fib() {
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

up<Def> main_of_expression(up<Exp> body) {
  std::vector<Name> formals;
  return mk<Def>("main",formals,mv(body));
}

up<Exp> make_call1(Name name, up<Exp> arg) {
  std::vector<up<Exp>> args;
  args.push_back(mv(arg));
  return mk<Call>(name,mv(args));
}

up<Prog> prog_everything() {
  std::vector<up<Def>> defs;
  defs.push_back(def_absdiff());
  defs.push_back(def_quad());
  defs.push_back(def_square());
  defs.push_back(def_fact());
  defs.push_back(def_fib());
  defs.push_back(main_of_expression(mk<Num>(42)));
  return mk<Prog>(mv(defs));
}

up<Prog> prog_quad() {
  std::vector<up<Def>> defs;
  defs.push_back(def_quad());
  defs.push_back(def_square());
  defs.push_back(main_of_expression(make_call1("quad",mk<Num>(3))));
  return mk<Prog>(mv(defs));
}

up<Prog> prog_fact() {
  std::vector<up<Def>> defs;
  defs.push_back(def_fact());
  defs.push_back(main_of_expression(make_call1("fact",mk<Num>(4))));
  return mk<Prog>(mv(defs));
}

up<Prog> prog_fib() {
  std::vector<up<Def>> defs;
  defs.push_back(def_fib());
  defs.push_back(main_of_expression(make_call1("fib",mk<Num>(11))));
  return mk<Prog>(mv(defs));
}

up<Prog> prog_example(std::string name) {
  if (name == "everything") return prog_everything(); // no main
  if (name == "quad") return prog_quad();
  if (name == "fact") return prog_fact();
  if (name == "fib") return prog_fib();
  printf("**No such example: %s\n", name.c_str());
  crash
}
