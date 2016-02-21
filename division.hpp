#ifndef DIVISION_HPP
#define DIVISION_HPP

#include "operator_interface.hpp"

class Division : public Operator {
public:
  long long eval(long long a, long long b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
  ~Division() {}
};

#endif
