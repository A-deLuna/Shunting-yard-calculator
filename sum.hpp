#ifndef SUM_HPP
#define SUM_HPP

#include "operator_interface.hpp"

class Sum : public Operator {
public:
  int eval(int a, int b) override;
  int precedence() override;
  int associativity() override;
  ~Sum() {}
};

#endif
