#include "sum.hpp"
#include <string>

Number Sum::eval(Number a, Number b) {
  Number ans = a + b;

  return ans;
}

int Sum::precedence() {
  return 2;
}

int Sum::associativity() {
  return assoc::LEFT;
}

int Sum::arity() {
  return 2;
}

std::string Sum::sign() {
  return "+";
}
