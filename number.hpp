#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "decimal.h"
class Number {
public:
  Number(dec::decimal<8> mantissa, dec::decimal<8> exponent);
  Number(std::string mantissa, std::string exponent);
  Number(int mantissa, int exponent);
  Number();

  Number operator-() const;
  Number operator+(const Number &b) const;
  Number operator-(const Number &b);
  Number operator*(const Number &b) const;
  Number operator/(const Number &b) const;
  void shl();
  void shr();
  dec::decimal<8> mantissa;
  dec::decimal<8> exponent;
private:
  void normalize();
};

inline bool operator<(const Number &a, const Number &b) {
  if(a.exponent < b.exponent) return true;
  if(a.exponent > b.exponent) return false;
  return a.mantissa <  b.mantissa;
}


inline bool operator>(const Number &a, const Number &b) {
  return b < a;
}
inline bool operator==(const Number &a, const Number &b) {
  return a.exponent == b.exponent && a.mantissa == b.mantissa;
}

inline std::ostream& operator<<(std::ostream& out, const Number &n) {
  return out << n.mantissa << "E" << n.exponent;
}

#endif
