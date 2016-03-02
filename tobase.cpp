#include "shunting-yard.hpp"
#include <iostream>
#include <bitset>
#include <sstream>
std::string toBase(long long n, int base) {
  std::stringstream s;
  if(base == 2) {
    std::bitset<sizeof(long long) * 8> bits(n);
    s << bits;
  }
  else if(base == 16) {
    s << std::hex<<n;
  }
  return s.str();
}
