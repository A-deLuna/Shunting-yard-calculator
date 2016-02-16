#ifndef OPERATOR_INTERFACE_HPP
#define OPERATOR_INTERFACE_HPP

enum assoc { LEFT, RIGHT };

class Operator {
public:
  virtual int eval(int a, int b) = 0;
  virtual int precedence() = 0;
  virtual int associativity() = 0;
  virtual ~Operator() {}
};
#endif
