#include "division.hpp"

long long Division::eval(long long a, long long b) {
  return b / a;
}

int Division::precedence() {
  return 3;
}

int Division::associativity() {
  return assoc::LEFT;
}
