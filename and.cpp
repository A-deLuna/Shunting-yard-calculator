#include "and.hpp"

Number And::eval(Number a, Number b) {
  return a * b;
}

int And::precedence() {
  return 0;
}

int And::associativity() {
  return assoc::LEFT;
}

int And::arity() {
  return 2;
}

std::string And::sign() {
  return "AND";
}
