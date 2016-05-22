#ifndef RIGHT_PAREN_HPP
#define RIGHT_PAREN_HPP

#include "operator_interface.hpp"

class RightParen: public Operator {
public: 
  std::string sign() override;
  int associativity() override;
  int precedence() override;
};

#endif
