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

class Exp {
public:
  virtual ~Exp() = default;
  virtual int eval(Env&) = 0;
  virtual std::string pp() = 0;
  virtual llvm::Value* codegen() = 0;
};

class Var : public Exp {
private:
  Name VarName;
public:
  Var (::Name VarName) : VarName(VarName) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Num : public Exp {
private:
  int NumValue;
public:
  Num (int NumValue) : NumValue(NumValue) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Mul : public Exp {
private:
  up<Exp> MulLeft;
  up<Exp> MulRight;
public:
  Mul (up<Exp> MulLeft, up<Exp> MulRight)
    : MulLeft(mv(MulLeft)), MulRight(mv(MulRight))
  {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Sub : public Exp {
private:
  up<Exp> SubLeft;
  up<Exp> SubRight;
public:
  Sub (up<Exp> SubLeft, up<Exp> SubRight)
    : SubLeft(mv(SubLeft)), SubRight(mv(SubRight))
  {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Call : public Exp {
  Name CallFunc;
  std::vector<up<Exp>> CallArgs;
public:
  Call(Name CallFunc, std::vector<up<Exp>> CallArgs)
    : CallFunc(CallFunc), CallArgs(mv(CallArgs)) {}
  int eval(Env&) override;
  std::string pp() override;
  llvm::Value* codegen() override;
};

class Def {
public:
  Name DefName;
private:
  std::vector<Name> DefFormals;
  up<Exp> DefBody;
public:
  Def(Name DefName, std::vector<Name> DefFormals, up<Exp> DefBody)
    : DefName(DefName), DefFormals(DefFormals), DefBody(mv(DefBody)) {}
  std::string pp();
  int apply(Env&,std::vector<int>);
};

class Prog {
  std::vector<up<Def>> ProgDefs;
  up<Exp> ProgMain;
public:
  Prog(std::vector<up<Def>> ProgDefs, up<Exp> ProgMain)
    : ProgDefs(mv(ProgDefs)), ProgMain(mv(ProgMain)) {}
  std::string pp();
  int eval();
};

#endif // AST_H
