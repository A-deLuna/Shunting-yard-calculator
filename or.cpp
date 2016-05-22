#include "or.hpp"

Number Or::eval(Number a, Number b) {
  return Number::abs(a) + Number::abs(b);
}

int Or::precedence() {
  return -1;
}

int Or::associativity() {
  return assoc::LEFT;
}

int Or::arity() {
  return 2;
}

std::string Or::sign() {
  return "OR";
}
