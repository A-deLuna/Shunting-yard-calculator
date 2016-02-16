#ifndef MULTIPLICATION_HPP
#define MULTIPLICATION_HPP

#include "operator_interface.hpp"

class Multiplication : public Operator {
public:
  int eval(int a, int b) override;
  int precedence() override;
  int associativity() override;
  ~Multiplication() {}
};

#endif
