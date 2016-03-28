#ifndef OPERATOR_INTERFACE_HPP
#define OPERATOR_INTERFACE_HPP

#define MAX_NUM 999999999999LL
#define MIN_NUM -999999999999LL

enum assoc {NONE, LEFT, RIGHT };

class Operator {
public:
  virtual long long eval(long long a, long long b) {}
  virtual int precedence() {}
  virtual int associativity() {}
  virtual int arity() {}
  virtual char sign() {}
  virtual ~Operator() {}
};
#endif
