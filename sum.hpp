#ifndef SUM_HPP
#define SUM_HPP

#include "operator_interface.hpp"

class Sum : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
  ~Sum() {}
};

#endif
