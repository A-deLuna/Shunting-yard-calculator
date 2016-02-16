#include "substraction.hpp"

int Substraction::eval(int a, int b) {
    return b - a;
}

int Substraction::precedence() {
    return 2;
}

int Substraction::associativity() {
    return assoc::LEFT;
}

