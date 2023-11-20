
#include "example.h"

std::unique_ptr<Exp> make_example() {
  auto e1 = std::make_unique<Var>("xx1");
  auto e2 = std::make_unique<Num>(8);
  auto e3 = std::make_unique<Var>("xx2");
  auto e4 = std::make_unique<Sub>(std::move(e2),std::move(e3));
  auto e5 = std::make_unique<Sub>(std::move(e1),std::move(e4));
  return e5;
}
