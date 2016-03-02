#ifndef OPERATOR_INTERFACE_HPP
#define OPERATOR_INTERFACE_HPP

#define MAX_NUM 999999999999LL
#define MIN_NUM -999999999999LL

enum assoc { LEFT, RIGHT };

class Operator {
public:
  virtual long long eval(long long a, long long b) = 0;
  virtual int precedence() = 0;
  virtual int associativity() = 0;
  virtual int arity() = 0;
  virtual char sign() = 0;
  virtual ~Operator() {}
};
#endif
