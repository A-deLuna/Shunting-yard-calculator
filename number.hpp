#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "decimal.h"
#include <map>
#include <utility>
#include <iostream>
#define PREC 8 
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
  void normalize();
private:
  void toZeroExp();
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

  //0.00000001
  if(a.exponent < dec::decimal_cast<PREC>(8) && 
     a.exponent > dec::decimal_cast<PREC>(-9)) {
    while(a.exponent != dec::decimal_cast<PREC>(0)) {
      if(a.exponent < dec::decimal_cast<PREC>(0)) {
        a.shr();
      }
      else {
        a.shl();
      }
    }
    
  }
  //if(a.exponent < dec::decimal_cast<PREC>(8) && a.exponent > dec::decimal_cast<PREC>(0)) {
  //  a.shl();
  //}
  //if(a.exponent > dec::decimal_cast<PREC>(-9) && a.exponent < dec::decimal_cast<PREC>(-1)) {
  //  a.shr();
  //}

  std::stringstream s;

  //std::cout<<"EXPONTENT" << a.exponent << '\n';
  //if(a.exponent == dec::decimal_cast<PREC>(0)) {
    dec::int64 before, after, au;
    a.mantissa.unpack(before, after) ;
    if(before != 0) {
      au = before;
      dec::decimal<PREC-1> aux = dec::decimal_cast<PREC-1>(a.mantissa);
      //std::cout<< "DEBUG BEFORE" << a.mantissa << '\n';
      a.mantissa = dec::decimal_cast<PREC>(aux);
      //std::cout<< "DEBUG AFTER" << a.mantissa << '\n';
      a.mantissa.unpack(before, after) ;
      if(au < before) {
        a.shr();
      }
    }
  //}

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
