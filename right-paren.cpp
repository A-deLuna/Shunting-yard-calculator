#include "right-paren.hpp"

std::string RightParen::sign() {
  return ")";
}

int RightParen::associativity() {
  return assoc::NONE;
}

int RightParen::precedence() {
  return 0;
}
