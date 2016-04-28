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
  static Number abs(Number n);
private:
  void toZeroExp();
  Number pow(Number x, Number y);
  Number nthRoot(Number x, Number a, Number n);
  Number factorial (int n);
  Number decimalExp(Number power);
  Number ln(Number n);
  Number ln2(Number number);
  Number preln(Number number);
  bool isFractional(dec::int64 & numerator, dec::int64 &  denominator) const;
  dec::int64 gcd(dec::int64 a, dec::int64 b);
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

inline int numbersize(dec::int64 n) {
  int count = 0;
  while(n) {
    count++;
    n/=10;
  }
  return count;
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
  dec::int64 before, after, au;
  a.mantissa.unpack(before, after) ;
  if(before != 0) {
    au = before;
    int i = numbersize(before);
      if(i == 1) {
        dec::decimal<PREC-1> aux = dec::decimal_cast<PREC-1>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 2) {
        dec::decimal<PREC-2> aux = dec::decimal_cast<PREC-2>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 3) {
        dec::decimal<PREC-3> aux = dec::decimal_cast<PREC-3>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 4) {
        dec::decimal<PREC-4> aux = dec::decimal_cast<PREC-4>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 5) {
        dec::decimal<PREC-5> aux = dec::decimal_cast<PREC-5>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 6) {
        dec::decimal<PREC-6> aux = dec::decimal_cast<PREC-6>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 7) {
        dec::decimal<PREC-7> aux = dec::decimal_cast<PREC-7>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        if(au < before) {
          a.shr();
        }
      }
      if(i == 8) {
        dec::decimal<PREC-8> aux = dec::decimal_cast<PREC-8>(a.mantissa);
        a.mantissa = dec::decimal_cast<PREC>(aux);
        a.mantissa.unpack(before, after) ;
        //if(au < before) {
        //  a.shr();
        //}
      }
    
  }

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
