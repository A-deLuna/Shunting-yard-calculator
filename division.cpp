#include "division.hpp"

int Division::eval(int a, int b) {
  return b / a;
}

int Division::precedence() {
  return 3;
}

int Division::associativity() {
  return assoc::LEFT;
}
