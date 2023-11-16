#ifndef AST_H
#define AST_H

#include <string>
#include <memory>

#define up std::unique_ptr // TODO: bad idiom?

class Exp {
public:
  //virtual ~Exp() = default; // TODO: does what? why needed?
  virtual int eval() = 0;
};

class Num : public Exp {
private:
  int num;
public:
  Num (int num) : num(num) {}
  int eval();
};

class Sub : public Exp {
private:
  up<Exp> left;
  up<Exp> right;
public:
  Sub (up<Exp> left, up<Exp> right)
    : left(std::move(left)), right(std::move(right))
  {}
  int eval();
};

#endif // AST_H
