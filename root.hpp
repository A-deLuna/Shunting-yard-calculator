#ifndef ROOT_HPP
#define ROOT_HPP

#include "operator_interface.hpp"

class Root : public Operator {
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  std::string sign() override;
};
#endif
