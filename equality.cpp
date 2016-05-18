#include "equality.hpp"

Number Equality::eval(Number a, Number b) {
  std::cout<<"B=" << b.mantissa << "E" << b.exponent <<'\n';
  std::cout<<"A=" << a.mantissa << "E" << a.exponent <<'\n';
  std::cout<< b << "==" << a << " = " << (b==a) <<  '\n';
  if(a == b) return Number("1","0");
  return Number("0","0");
}

int Equality::precedence() {
  return 0;
}

int Equality::associativity() {
  return assoc::LEFT;
}

int Equality::arity() {
  return 2;
}

char Equality::sign() {
  return '=';
}
