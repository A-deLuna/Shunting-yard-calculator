#include "right-paren.hpp"

char RightParen::sign() {
  return ')';
}

int RightParen::associativity() {
  return assoc::NONE;
}

int RightParen::precedence() {
  return 0;
}
