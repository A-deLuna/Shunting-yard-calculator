#ifndef MULTIPLICATION_HPP
#define MULTIPLICATION_HPP

#include "operator_interface.hpp"

class Multiplication : public Operator {
public:
  long long eval(long long a, long long b) override;
  int precedence() override;
  int associativity() override;
  ~Multiplication() {}
};

#endif
