#include "multiplication.hpp"

long long Multiplication::eval(long long a, long long b) {
  return a * b;
}

int Multiplication::precedence() {
  return 3;
}

int Multiplication::associativity() {
  return assoc::LEFT;
}
