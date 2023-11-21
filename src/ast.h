#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include "misc.h"

namespace llvm {
  class Value;
}

// TODO: use "ast" namespace?

typedef std::string Name;

class Env;

class Exp {
public:
  virtual ~Exp() = default;
  virtual int eval(Env&) = 0;
  virtual std::string pp() = 0;
  virtual llvm::Value* codegen() = 0;
};

class Var : public Exp {
private:
  Name name;
public:
  Var (Name name) : name(name) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Num : public Exp {
private:
  int num;
public:
  Num (int num) : num(num) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Mul : public Exp {
private:
  up<Exp> left;
  up<Exp> right;
public:
  Mul (up<Exp> left, up<Exp> right)
    : left(mv(left)), right(mv(right))
  {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Sub : public Exp {
private:
  up<Exp> left;
  up<Exp> right;
public:
  Sub (up<Exp> left, up<Exp> right)
    : left(mv(left)), right(mv(right))
  {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Call1 : public Exp {
  Name func;
  up<Exp> arg; // TODO: many args
public:
  Call1(Name func, up<Exp> arg) : func(func), arg(mv(arg)) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Def {
public:
  Name name;
private:
  Name formal; // TODO: many formals
  up<Exp> body;
public:
  Def(Name name, Name formal, up<Exp> body)
    : name(name), formal(formal), body(mv(body)) {}
  std::string pp();
  int apply(Env&,int);
};

class Prog {
  up<Def> theDef; // TODO: many defs
  up<Exp> main;
public:
  Prog(up<Def> theDef, up<Exp> main) : theDef(mv(theDef)), main(mv(main)) {}
  std::string pp();
  int eval();
};

#endif // AST_H
