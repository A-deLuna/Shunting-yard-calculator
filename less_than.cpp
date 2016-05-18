#include "less_than.hpp"

Number LessThan::eval(Number a, Number b) {
  if(b < a) return Number("1","0");
  return Number("0","0");
}

int LessThan::precedence() {
  return 1;
}

int LessThan::associativity() {
  return assoc::LEFT;
}

int LessThan::arity() {
  return 2;
}

char LessThan::sign() {
  return '<';
}
