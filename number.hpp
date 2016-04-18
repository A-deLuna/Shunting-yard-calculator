#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "decimal.h"
#include <map>
#include <utility>
#define PREC 7
class Number {
public:
  Number(dec::decimal<PREC> mantissa, dec::decimal<PREC> exponent);
  Number(std::string mantissa, std::string exponent);
  Number(int mantissa, int exponent);
  Number();

  Number operator-() const;
  Number operator+(const Number &b) const;
  Number operator-(const Number &b);
  Number operator*(const Number &b) const;
  Number operator/(const Number &b) const;
  Number operator^(const Number &b);
  bool operator<(const Number &b) const;
  bool operator==(const Number &b) const;
  bool isRational() const;
  void shl();
  void shr();
  dec::decimal<PREC> mantissa;
  dec::decimal<PREC> exponent;
private:
  void toZeroExp();
  void normalize();
  Number abs(Number n);
  Number pow(Number x, Number y);
  Number nthRoot(Number a, Number n);
};
static std::map<std::pair<Number, Number> , Number > powers;


inline bool operator>(const Number &a, const Number &b) {
  return b < a;
}

inline bool operator<=(const Number &a, const Number &b) {
  return a < b || a == b;
}

inline bool operator>=(const Number &a, const Number &b) {
  return a > b || a == b;
}

inline std::ostream& operator<<(std::ostream& out, const Number &n) {
  // this wont wont with exponents like 0.5. Let's worry about that later thou
  Number a(n);

  if(a.exponent < dec::decimal_cast<PREC>(8) && 
     a.exponent > dec::decimal_cast<PREC>(-8)) {
    while(a.exponent != dec::decimal_cast<PREC>(0)) {
      if(a.exponent < dec::decimal_cast<PREC>(0)) {
        a.shr();
      }
      else {
        a.shl();
      }
    }
    
  }
  std::stringstream s;
  s << a.mantissa;
  std::string mant = s.str();
  int pos = mant.find_last_not_of("0");
  if( pos != std::string::npos) {
    if(mant[pos] != '.'){
      pos++;
    }
  }
  out << mant.substr(0, pos);

  if(a.exponent != dec::decimal_cast<PREC>(0)) {
    s.str("");
    s << a.exponent;
    std::string exp = s.str();
    pos = exp.find('.');
    out << 'E' << exp.substr(0,pos);
  }
  return out;
}

#endif
