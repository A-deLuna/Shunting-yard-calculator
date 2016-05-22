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

std::string Negative::sign() {
  return "_";
}
