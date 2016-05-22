#include "equality.hpp"

Number Equality::eval(Number a, Number b) {
  if(a == b) return Number("1","0");
  return Number("0","0");
}

int Equality::precedence() {
  return 0;
}

int Equality::associativity() {
  return assoc::LEFT;
}

int Equality::arity() {
  return 2;
}

char Equality::sign() {
  return '=';
}
