#include "negative.hpp"

long long Negative::eval(long long a, long long b) {
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
