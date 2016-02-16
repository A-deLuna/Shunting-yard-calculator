#include "multiplication.hpp"

int Multiplication::eval(int a, int b) {
  return a * b;
}

int Multiplication::precedence() {
  return 3;
}

int Multiplication::associativity() {
  return assoc::LEFT;
}
