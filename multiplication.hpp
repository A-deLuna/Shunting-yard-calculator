#ifndef MULTIPLICATION_HPP
#define MULTIPLICATION_HPP

#include "operator_interface.hpp"

class Multiplication : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
  ~Multiplication() {}
};

#endif
