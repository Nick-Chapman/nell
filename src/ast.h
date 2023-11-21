#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <vector>
#include "misc.h"

namespace llvm {
  class Value;
}

// TODO: use "ast" namespace?

typedef std::string Name;

class Env;

// TODO: use upper case names for members

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

class Call : public Exp {
  Name func;
  std::vector<up<Exp>> args;
public:
  Call(Name func, std::vector<up<Exp>> args) : func(func), args(mv(args)) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Def {
public:
  Name name;
private:
  std::vector<Name> formals;
  up<Exp> body;
public:
  Def(Name name, std::vector<Name> formals, up<Exp> body)
    : name(name), formals(formals), body(mv(body)) {}
  std::string pp();
  int apply(Env&,std::vector<int>);
};

class Prog {
  std::vector<up<Def>> theDefs;
  up<Exp> main;
public:
  Prog(std::vector<up<Def>> theDefs, up<Exp> main)
    : theDefs(mv(theDefs)), main(mv(main)) {}
  std::string pp();
  int eval();
};

#endif // AST_H
