#include "number.hpp"
#include <iostream>
#define ROOT_PREC "0.000001"

Number::Number(dec::decimal<PREC> mantissa, dec::decimal<PREC> exponent) 
  : mantissa(mantissa), exponent(exponent) {
  normalize();
}

Number::Number(std::string mantissa, std::string exponent) {
    int e_pos = mantissa.find("E");

    if(e_pos == std::string::npos) {
        this->mantissa = dec::decimal<PREC>(mantissa);
        this->exponent = dec::decimal<PREC>(exponent);
    }
    else {
      std::string mant = mantissa.substr(0, e_pos);
      std::string exp = mantissa.substr(e_pos+1);
      this->mantissa = dec::decimal<PREC>(mant);
      this->exponent = dec::decimal<PREC>(exp);
    }
  normalize();
}

Number::Number(int mantissa, int exponent) 
  : mantissa(mantissa), exponent(exponent) {
  normalize();
}
Number::Number() 
  : mantissa(0), exponent(0) {
}

void Number::normalize() {
  while(mantissa > dec::decimal_cast<PREC>(0) && mantissa < dec::decimal_cast<PREC>(1)) {
    shl();
  }
  while(mantissa >= dec::decimal_cast<PREC>(10) || mantissa <= dec::decimal_cast<PREC>(-10)) {
    shr();
  }
  // this fix is for the case 0.3333333 - 1/3 which has mantssa 0 but exponent -1
  if( mantissa == dec::decimal_cast<PREC>(0)) {
    exponent = dec::decimal_cast<PREC>(0);
  }
}

Number Number::operator+(const Number &b) const {
  Number smlr = std::min(*this, b);
  Number gtr = std::max(*this, b);

  while(smlr.exponent < gtr.exponent) {
    smlr.shr();
  }

  Number ans(gtr.mantissa + smlr.mantissa, gtr.exponent);
  return ans;
}

Number Number::operator-(const Number &b) {
  Number b_cpy(b);
  Number * smlr =  (*this < b_cpy) ? this : &b_cpy;
  Number gtr = std::max(*this, b_cpy);

  while(smlr->exponent < gtr.exponent) {
    smlr->shr();
  }

  Number ans(this->mantissa - b_cpy.mantissa, gtr.exponent);
  return ans;
}

Number Number::operator*(const Number &b) const {
  //std::cout<< this -> mantissa << ": E" << this->exponent << "\n"; 
  //std::cout<< b.mantissa << ": E" <<b.exponent << "\n"; 
  Number ans (this->mantissa * b.mantissa , this->exponent + b.exponent);
  //std::cout<< ans.mantissa << ": E" <<ans.exponent << "\n"; 
  return ans;
}

Number Number::operator/(const Number &b) const {
  Number ans (this->mantissa / b.mantissa , this->exponent - b.exponent);
  return ans;
}

Number Number::operator-() const {
  Number n ("-1", "0");
  return *this * n;
}

bool Number::operator<(const Number &b) const {
  if(this->mantissa == dec::decimal_cast<PREC>(0)) {
    return b.mantissa > dec::decimal_cast<PREC>(0);
  } 

  if(b.mantissa == dec::decimal_cast<PREC>(0)) {
    return this->mantissa < dec::decimal_cast<PREC>(0);
  }

  if(this->mantissa < dec::decimal_cast<PREC>(0) && 
      b.mantissa >= dec::decimal_cast<PREC>(0)) {
    return true;
  } 

  if(b.mantissa < dec::decimal_cast<PREC>(0) &&
    this->mantissa >=  dec::decimal_cast<PREC>(0)) {
    return false;
  }
  if(b.mantissa < dec::decimal_cast<PREC>(0) &&
    this->mantissa <  dec::decimal_cast<PREC>(0)) {
    if(this->exponent < b.exponent) return false;
    if(this->exponent > b.exponent) return true;
  }

  if(this->exponent < b.exponent) return true;
  if(this->exponent > b.exponent) return false;
  return this->mantissa <  b.mantissa;
}
bool Number::operator==(const Number &b) const {
  return this->exponent == b.exponent && this->mantissa == b.mantissa;
}

Number Number::operator^(const Number &b) {
  
  return pow(*this, b);
}


Number Number::abs(Number n) {
  if(n < Number("0","0")) return -n;
  return n;
}

Number Number::pow(Number x, Number y) {
  if(y == Number(0,0)) {
    Number ans = Number(1,0);
    return ans;
  }
  if(y == Number(1,0)) {
    Number ans = x;
    return ans;
  }
  if(y < Number(0,0)) {
    return pow(Number(1,0) / x, -y);
  }
  if(y.isRational()) {
    dec::int64 numerator, denominator;
    if(y.isFractional(numerator, denominator)) {
    }
    else {
      Number aux(y);
      aux.toZeroExp();
      dec::int64 before, after;
      aux.mantissa.unpack(before, after);
      dec::int64 count = 1;
      while(after != 0) {
        aux.mantissa *= dec::decimal_cast<PREC>(10);
        aux.mantissa.unpack(before, after);
        count *= 10;
      }
      numerator = before;
      denominator = count;
    }
    dec::int64 g = gcd(numerator, denominator);

    numerator /= g;
    denominator /= g;
    
    Number neg = Number(1,0);
    if(x < Number(0,0)) {
      if(denominator%2ll == 0) {
        throw std::string("negative root exception with even base");
      }
      neg = Number("-1","0");
      x = -x;
    }

    Number a = y * preln(x);
    return neg * decimalExp(a);

  }
  Number ans = Number ("1", "0");
  for(Number i = Number("0","0"); i < y; i = i + Number("1","0")) {
    if(ans > Number("9.9999999E99", "0") || ans < Number("-9.9999999E99", "0")) {
      throw std::string("Number out of valid range");
    }
    ans = x * ans;
  }
  return ans;

}

dec::int64 Number::gcd(dec::int64 a, dec::int64 b) {
  if( b == 0) return a;
  return gcd(b, a % b);
}

Number Number::factorial (int n) {
  if(n == 0) return Number ("1", "0");
  if(n == 1) return Number ("1", "0");
  return Number(n, 0) * factorial(n-1);
}

Number Number::decimalExp(Number power) {
  Number result("1","0");
  for(int iter = 1; iter < 450; iter++ ) {
    Number factoria = factorial(iter);
    result = result + pow(power, Number(iter, 0)) / factoria;
  }
  return result;
} 

Number Number::ln(Number n) {
  Number x = (n - Number(1,0)) / (n + Number(1,0));

  Number ans = Number(0,0);
  for(int i = 1; i < 500 ; i += 2) {
    ans = ans +  Number(2,0) * pow(x, Number(i,0))/ Number(i,0) ;
  }
  return ans;
}

Number Number::preln(Number number) {
  int i = 0;
  while(number >= Number(281,0)) {
    number = number /Number(281,0);
    i++;
  }
  //cout << "number beforeLogN: " << number << '\n';

  //ln 281
  return Number("5.6383546","0") * Number(i,0) + ln(number);
}

Number Number::nthRoot(Number x, Number a, Number n) {
  // cant take sqrt of negative number
  if(a < Number ("0", "0")) 
    throw std::string("negative sqrt exception");

  Number d = Number(a.exponent,dec::decimal_cast<PREC>(0));
  Number current =  x;
  Number previous = Number("1", "1");
  Number aux = n - Number("1","0");
  do {
    //std::cout<< current;
    previous = current;
    current = (aux * previous + a / pow(previous, aux)) / n;
    //std::cout<<"CALLED NTHROOT" << "\n";
    //std::cout<< ": "<< abs(previous - current)<< "\n";
  } while(abs(previous - current) > Number(ROOT_PREC, "0"));
  return current;

}
bool Number::isFractional(dec::int64 & numerator, dec::int64 & denominator) const {
  Number aux(*this);
  Number ans = aux * Number(10,0) - aux;
  dec::int64 before, after;
  ans.toZeroExp();
  ans.mantissa.unpack(before, after);
  std::string s = std::to_string(after);
  if(after == 0) {
    numerator = (before ) ;
    denominator = 9 ;
    return true;
  }
  if(s.size() >= 5 && s[0] == '9' && s[1] == '9' && s[2] == '9' && s[3] == '9'&& s[4] == '9') {
    numerator = (before + 1) ;
    denominator = 9 ;
    return true;
  }
  if(s.size() >= 5 && s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '0'&& s[4] == '0') {
    numerator = (before ) ;
    denominator = 9 ;
    return true;
  }
  return false;
}

bool Number::isRational() const {
  if(this->exponent >= dec::decimal_cast<PREC>(PREC + 1)) {
    return false;
  }
  Number aux(*this);
  aux.toZeroExp();

  dec::int64 before, after;
  aux.mantissa.unpack(before, after);
  if(after == 0) {
    return false;
  }

  return true;
}

void Number::toZeroExp() {
  while(this->exponent < dec::decimal_cast<PREC>(0)) {
    this->shr();
  }

  while(this->exponent > dec::decimal_cast<PREC>(0)) {
    this->shl();
  }
}


void Number::shl() {
  mantissa *= dec::decimal_cast<PREC>(10);
  exponent -= dec::decimal_cast<PREC>(1);
}
void Number::shr() {
  mantissa /= dec::decimal_cast<PREC>(10);
  exponent += dec::decimal_cast<PREC>(1);
}
