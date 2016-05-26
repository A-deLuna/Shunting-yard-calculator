#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "decimal.h"
#include <map>
#include <utility>
#include <iostream>
#define PREC 8 
enum class Formato {
  FIJO,
  REAL, NC,
  ESTANDAR
};

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
  static Number nthRoot(Number a, Number n);
  static Number pow(Number x, Number y);
  static Number ln(Number n);
  static Number ln2(Number number);
  static Number preln(Number number);
  static dec::int64 gcd(dec::int64 a, dec::int64 b);
  static Number decimalExp(Number power);
  static Number factorial (int n);
  static Formato formato;
  static long fijo_size;
  void toZeroExp();
private:
  bool isFractional(dec::int64 & numerator, dec::int64 &  denominator) const;
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

inline std::string estandar(const Number &n) {
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

  // esta pendejada es para cuando despues de llevar el exponente a cero nos 
  // queda algo como 1234.343435455, pero queremos solo imprimir 1234.3434 
  // asi que lo que hacemos es castearlo a la precision adecuada
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
        //  a.shr(); }
      }
    
  }
  //copy pasterino rip
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

  s << a.mantissa;
  std::string mant = s.str();
  int pos = mant.find_last_not_of("0");
  if( pos != std::string::npos) {
    if(mant[pos] != '.'){
      pos++;
    }
  }
  std::stringstream ans;
  ans << mant.substr(0, pos);

  if(a.exponent != dec::decimal_cast<PREC>(0)) {
    s.str("");
    s << a.exponent;
    std::string exp = s.str();
    pos = exp.find('.');
    ans << 'E' << exp.substr(0,pos);
  }
  return ans.str();

}
inline std::string notacion(const Number &n) {
  std::stringstream s;
  std::stringstream ans;
  s << n.mantissa;
  std::string mant = s.str();
  int pos = mant.find_last_not_of("0");
  if( pos != std::string::npos) {
    if(mant[pos] != '.'){
      pos++;
    }
  }
  ans << mant.substr(0, pos);
  s.str("");
  s << n.exponent;
  std::string exp = s.str();
  pos = exp.find('.');
  ans << 'E' << exp.substr(0,pos);
  return ans.str();

}
inline std::string real(const Number& n) {
  std::stringstream ans;
  std::string num = estandar(n);
  if(num.find(".") == std::string::npos) {
    if(n.exponent < dec::decimal_cast<PREC>(8) && 
       n.exponent > dec::decimal_cast<PREC>(-9)) {
        num +=".0";
    }
    else {
      num.insert(num.find("E"), ".0");
    }
  }

  ans << num;
  return ans.str();
}
inline std::string fijo(const Number& n) {
  std::stringstream ans;
  std::string num = real(n);
  Number a(n);
  int pos = num.find(".");
  int decimals;
  if(a.exponent < dec::decimal_cast<PREC>(8) && 
     a.exponent > dec::decimal_cast<PREC>(-9)) {
     decimals = num.size() - pos - 1;
  }
  else {
    decimals = num.find("E") - pos -1;
  }


  if(decimals < Number::fijo_size) {
    for(int i = 0; i < Number::fijo_size - decimals; ++i)  {
      if(a.exponent < dec::decimal_cast<PREC>(8) && 
         a.exponent > dec::decimal_cast<PREC>(-9)) {
          num += "0";
      }
      else {
          num.insert(num.find("E"), "0");
      }
    }
  }
  if (decimals > Number::fijo_size) {
    std::stringstream s;
    std::cout<<a.mantissa << "E" << a.exponent << '\n';  
    if(a.exponent < dec::decimal_cast<PREC>(8) && 
       a.exponent > dec::decimal_cast<PREC>(-9)) {
      a.toZeroExp();
    }
      int i = Number::fijo_size;
        if(i == 7) {
          dec::decimal<PREC-1> aux = dec::decimal_cast<PREC-1>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 6) {
          dec::decimal<PREC-2> aux = dec::decimal_cast<PREC-2>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 5) {
          dec::decimal<PREC-3> aux = dec::decimal_cast<PREC-3>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 4) {
          dec::decimal<PREC-4> aux = dec::decimal_cast<PREC-4>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 3) {
          dec::decimal<PREC-5> aux = dec::decimal_cast<PREC-5>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 2) {
          dec::decimal<PREC-6> aux = dec::decimal_cast<PREC-6>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        if(i == 1) {
          dec::decimal<PREC-7> aux = dec::decimal_cast<PREC-7>(a.mantissa);
          a.mantissa = dec::decimal_cast<PREC>(aux);
        }
        //TODO validar que fijo size no sea menor a 1
    std::cout<<a.mantissa << "E" << a.exponent << '\n';  
    return fijo(a);
  }
  ans << num;

  return  ans.str();
}

inline std::ostream& operator<<(std::ostream& out, const Number &n) {
  switch(Number::formato) {
    case Formato::NC: out << notacion(n);
    break;
    //case Formato::FIJO: return estandar(out, n);
    case Formato::ESTANDAR: out << estandar(n);
    break;
    case Formato::REAL: out << real(n);
    break;
    case Formato::FIJO: out << fijo(n);
    break;
    default: out << estandar(n);
  }
  return out;
}

#endif
