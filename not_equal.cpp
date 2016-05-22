#include "not_equal.hpp"

Number NotEqual::eval(Number a, Number b) {
  if(a == b) return Number("0","0");
  return Number("1","0");
}

int NotEqual::precedence() {
  return 0;
}

int NotEqual::associativity() {
  return assoc::LEFT;
}

int NotEqual::arity() {
  return 2;
}

std::string NotEqual::sign() {
  return "<>";
}
