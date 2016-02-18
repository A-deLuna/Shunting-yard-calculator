#ifndef SUM_HPP
#define SUM_HPP

#include "operator_interface.hpp"

class Sum : public Operator {
public:
  long long eval(long long a, long long b) override;
  int precedence() override;
  int associativity() override;
  ~Sum() {}
};

#endif
