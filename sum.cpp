#include "sum.hpp"

int Sum::eval(int a, int b) {
  return a + b;
}

int Sum::precedence() {
  return 2;
}

int Sum::associativity() {
  return assoc::LEFT;
}
