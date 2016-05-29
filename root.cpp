#include "root.hpp"

Number Root::eval(Number a, Number b) {
  Number aux(b);  
  aux.toZeroExp();
  dec::int64 before, after; 
  aux.mantissa.unpack(before, after);
  if(after == 0) {
    return Number::nthRoot(a, b) ; 
  }
  else {
    aux.mantissa.pack(before, 0);
    aux.normalize();
    return Number::nthRoot(a, aux) ; 

  }
}

std::string Root::sign() {
  return "r";
}

int Root::associativity() {
  return assoc::NONE;
}

int Root::precedence() {
  return 0;
}
