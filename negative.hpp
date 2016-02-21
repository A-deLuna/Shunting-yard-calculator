#ifndef NEGATIVE_HPP
#define NEGATIVE_HPP

#include "operator_interface.hpp"

class Negative : public Operator {
public:
  long long eval(long long a, long long b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
  ~Negative() {}
};

#endif
