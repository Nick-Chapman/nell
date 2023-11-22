
#include "example1.h"

using namespace ast1;

class WithGen {
  Gen& gen;
public:
  WithGen(Gen& gen) : gen(gen) {}

  Def& def_absdiff() {
    std::vector<Name> formals;
    formals.push_back("x");
    formals.push_back("y");
    auto& body = gen.ite(gen.lessThan(gen.var("x"),gen.var("y")),
                        gen.sub(gen.var("y"),gen.var("x")),
                        gen.sub(gen.var("x"),gen.var("y")));
    return gen.def("absdiff",formals,body);
  }

  Def& def_square() {
    std::vector<Name> formals;
    formals.push_back("x");
    return
      gen.def("square",formals,
              gen.mul(gen.var("x"),gen.var("x")));
  }

  Def& def_quad() {
    std::vector<Name> formals;
    formals.push_back("x");
    std::vector<Exp*> innerArgs;
    innerArgs.push_back(&gen.var("x"));
    auto& inner = gen.call("square",innerArgs);
    std::vector<Exp*> outerArgs;
    outerArgs.push_back(&inner);
    auto& outer = gen.call("square",outerArgs);
    return gen.def("quad",formals,outer);
  }

  Def& def_fact() {
    std::vector<Name> formals;
    formals.push_back("n");
    std::vector<Exp*> nestArgs;
    nestArgs.push_back(&gen.sub(gen.var("n"),gen.num(1)));
    auto& body =
      gen.ite(gen.lessThan(gen.var("n"),gen.num(1)),
              gen.num(1),
              gen.mul(gen.var("n"),gen.call("fact",nestArgs)));
    return gen.def("fact",formals,body);
  }

  Def& def_fib() {
    std::vector<Name> formals;
    formals.push_back("n");
    std::vector<Exp*> leftArgs;
    leftArgs.push_back(&gen.sub(gen.var("n"),gen.num(1)));
    std::vector<Exp*> rightArgs;
    rightArgs.push_back(&gen.sub(gen.var("n"),gen.num(2)));
    auto& body =
      gen.ite(gen.lessThan(gen.var("n"),gen.num(2)),
              gen.var("n"),
              gen.add(gen.call("fib",leftArgs),
                      gen.call("fib",rightArgs)));
    return gen.def("fib",formals,body);
  }

  Def& main_of_expression(Exp& body) {
    std::vector<Name> formals;
    return gen.def("main",formals,body);
  }

  Exp& make_call1(Name name, Exp& arg) {
    std::vector<Exp*> args;
    args.push_back(&arg);
    return gen.call(name,args);
  }

  Prog& prog_everything() {
    std::vector<Def*> defs;
    defs.push_back(&def_absdiff());
    defs.push_back(&def_quad());
    defs.push_back(&def_square());
    defs.push_back(&def_fact());
    defs.push_back(&def_fib());
    defs.push_back(&main_of_expression(gen.num(42)));
    return gen.prog(defs);
  }

  Prog& prog_quad() {
    std::vector<Def*> defs;
    defs.push_back(&def_quad());
    defs.push_back(&def_square());
    defs.push_back(&main_of_expression(make_call1("quad",gen.num(3))));
    return gen.prog(defs);
  }

  Prog& prog_fact() {
    std::vector<Def*> defs;
    defs.push_back(&def_fact());
    defs.push_back(&main_of_expression(make_call1("fact",gen.num(4))));
    return gen.prog(defs);
  }

  Prog& prog_fib() {
    std::vector<Def*> defs;
    defs.push_back(&def_fib());
    defs.push_back(&main_of_expression(make_call1("fib",gen.num(11))));
    return gen.prog(defs);
  }

  Prog& prog_example(std::string name) {
    if (name == "everything") return prog_everything(); // no main
    if (name == "quad") return prog_quad();
    if (name == "fact") return prog_fact();
    if (name == "fib") return prog_fib();
    printf("**No such example: %s\n", name.c_str());
    crash;
  }

};

namespace ast1 {
  Prog& prog_example(Gen& gen,std::string name) {
    return WithGen(gen).prog_example(name);
  }
}
