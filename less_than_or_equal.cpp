#include "less_than_or_equal.hpp"
Number LessThanOrEqual::eval(Number a, Number b) {
  if(b < a || b == a) return Number("1","0");
  return Number("0","0");
}

int LessThanOrEqual::precedence() {
  return 1;
}

int LessThanOrEqual::associativity() {
  return assoc::LEFT;
}

int LessThanOrEqual::arity() {
  return 2;
}

char LessThanOrEqual::sign() {
  return 'l';
}
