#ifndef DIVISION_HPP
#define DIVISION_HPP

#include "operator_interface.hpp"

class Division : public Operator {
public:
  int eval(int a, int b) override;
  int precedence() override;
  int associativity() override;
  ~Division() {}
};

#endif
