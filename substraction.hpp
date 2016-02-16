#ifndef SUBSTRACTION_HPP
#define SUBSTRACTION_HPP

#include "operator_interface.hpp"

class Substraction : public Operator {
public:
  int eval(int a, int b) override;
  int precedence() override;
  int associativity() override;
  ~Substraction() {}
};

#endif
