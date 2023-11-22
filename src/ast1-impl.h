
#include "ast1.h"
#include "misc.h"

namespace llvm {
  class Value;
}

namespace ast1 {

  class Env; // namespace? eval
  class TopCon; // codegen.cpp
  class DefCon; // codegen.cpp

  class Exp {
  public:
    virtual ~Exp() = default;
    virtual std::string pp() = 0;
    virtual int eval(Env&) = 0;
    virtual llvm::Value* codegen(DefCon&) = 0; // codegen.cpp
  };

  class Num : public Exp {
    int NumValue;
  public:
    Num (int NumValue) : NumValue(NumValue) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Var : public Exp {
    Name VarName;
  public:
    Var (Name VarName) : VarName(VarName) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Mul : public Exp {
    Exp& MulLeft;
    Exp& MulRight;
  public:
    Mul (Exp& MulLeft, Exp& MulRight) : MulLeft(MulLeft), MulRight(MulRight) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Add : public Exp {
    Exp& AddLeft;
    Exp& AddRight;
  public:
    Add (Exp& AddLeft, Exp& AddRight) : AddLeft(AddLeft), AddRight(AddRight) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Sub : public Exp {
    Exp& SubLeft;
    Exp& SubRight;
  public:
    Sub (Exp& SubLeft, Exp& SubRight) : SubLeft(SubLeft), SubRight(SubRight) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class LessThan : public Exp {
    Exp& LessThanLeft;
    Exp& LessThanRight;
  public:
    LessThan (Exp& LessThanLeft, Exp& LessThanRight) : LessThanLeft(LessThanLeft), LessThanRight(LessThanRight) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Ite : public Exp {
    Exp& IteCond;
    Exp& IteThen;
    Exp& IteElse;
  public:
    Ite (Exp& IteCond, Exp& IteThen, Exp& IteElse)
      : IteCond(IteCond), IteThen(IteThen), IteElse(IteElse) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Call : public Exp {
    Name CallFunc;
    ExpList CallArgs;
  public:
    Call(Name CallFunc, ExpList CallArgs) : CallFunc(CallFunc), CallArgs(CallArgs) {}
    std::string pp() override;
    int eval(Env&) override;
    llvm::Value* codegen(DefCon&) override;
  };

  class Def {
  public:
    Name DefName;
  private:
    std::vector<Name> DefFormals;
    Exp& DefBody;
  public:
    Def(Name DefName, std::vector<Name> DefFormals, Exp& DefBody)
      : DefName(DefName), DefFormals(DefFormals), DefBody(DefBody) {}
    std::string pp();
    int apply(Env&,std::vector<int>);
    void declare(TopCon&);
    void codegen(TopCon&);
  };

  class Prog {
  public:
    DefList ProgDefs;
    Prog(DefList ProgDefs) : ProgDefs(ProgDefs) {}
    //std::string pp();
    //int eval();
    //ast1::Prog& toAst1(ast1::Gen&);
  };
}
