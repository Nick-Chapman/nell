#ifndef AST1_H
#define AST1_H

#include "misc.h"
#include <memory>
#include <string>
#include <vector>

namespace ast1 {

  typedef std::string Name;

  class Exp;
  class Def;
  class Prog;

  typedef std::vector<Name> NameList;
  typedef std::vector<Def*> DefList;
  typedef std::vector<Exp*> ExpList;

  class Gen {
  private:
    std::vector<Exp*> Exps;
    std::vector<Def*> Defs;
    std::vector<Prog*> Progs;
  public:
    ~Gen();
    Exp& var(Name);
    Exp& num(int);
    Exp& mul(Exp&,Exp&);
    Exp& add(Exp&,Exp&);
    Exp& sub(Exp&,Exp&);
    Exp& lessThan(Exp&,Exp&);
    Exp& ite(Exp&,Exp&,Exp&);
    Exp& call(Name,ExpList);
    Def& def(Name,NameList formals,Exp& body);
    Prog& prog(DefList);
  };

  int eval(Prog&);
  std::string pp(Prog&);
  void codegen(Prog&);

}

#endif // AST1_H
