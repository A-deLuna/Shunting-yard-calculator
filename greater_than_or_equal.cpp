#include "greater_than_or_equal.hpp"
Number GreaterThanOrEqual::eval(Number a, Number b) {
  if(b > a || b == a) return Number("1","0");
  return Number("0","0");
}

int GreaterThanOrEqual::precedence() {
  return 1;
}

int GreaterThanOrEqual::associativity() {
  return assoc::LEFT;
}

int GreaterThanOrEqual::arity() {
  return 2;
}

std::string GreaterThanOrEqual::sign() {
  return ">=";
}
