#include "negative.hpp"

Number Negative::eval(Number a, Number b) {
  return -a;
}

int Negative::precedence() {
  return 10;
}

int Negative::associativity() {
  return assoc::RIGHT;
}

int Negative::arity() {
  return 1;
}

char Negative::sign() {
  return '_';
}
