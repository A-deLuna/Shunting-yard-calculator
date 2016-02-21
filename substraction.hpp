#ifndef SUBSTRACTION_HPP
#define SUBSTRACTION_HPP

#include "operator_interface.hpp"

class Substraction : public Operator {
public:
  long long eval(long long a, long long b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
  ~Substraction() {}
};

#endif
