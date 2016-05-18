#include "greater_than.hpp"

Number GreaterThan::eval(Number a, Number b) {
  if(b > a) return Number("1","0");
  return Number("0","0");
}

int GreaterThan::precedence() {
  return 1;
}

int GreaterThan::associativity() {
  return assoc::LEFT;
}

int GreaterThan::arity() {
  return 2;
}

char GreaterThan::sign() {
  return '>';
}
