#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <limits>

#include "Test.h"

uint32_t p_mask = 0;
uint32_t n_mask = 1;

int inputError() {
    std::cerr << "Неверный формат ввода";
    return -1;
}

void checkString(const std::string & input_string) {
    for (char c : input_string) {
        if (c != '0' && c != '1' && c != 'x') {
            exit(inputError());
        }
    }
}

void fiInExp(Float & fl) {
    fl.exponent = 0b01111111 + ((rand() % 2) ? rand() % 8 : -rand() % 8);
}

void Float::mask() {
    ival &= n_mask;
    ival |= p_mask;
}

void fillMask(std::string input_string) {
    for (char c : input_string) {
        p_mask <<= 1;
        if (c == '1')
            p_mask |= 1;
        n_mask <<= 1;
        if (c != '0')
            n_mask |= 1;
    }
}

int main(int argc, char const *argv[]) {
    using namespace std;
    
    string mantissa, order;
    cin >> mantissa;
    if (mantissa.length() != 23)
        return inputError();
    checkString(mantissa);
    cin >> order;
    if (order.length() != 8)
        return inputError();
    checkString(order);

    fillMask(order);
    fillMask(mantissa);

    while (!Test::complited()) {
        Float a;
        Float b;
        {
            a.ival = rand();
            b.ival = rand();
            fiInExp(a);
            fiInExp(b);
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = rand();
            b.ival = ~rand();
            fiInExp(a);
            fiInExp(b);
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = ~rand();
            b.ival = ~rand();
            fiInExp(a);
            fiInExp(b);
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        // Special cases
        {
            a.fval = NAN;
            b.ival = rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = INFINITY;
            b.ival = ~rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = -INFINITY;
            b.ival = rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = 0;
            b.ival = ~rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = -.0f;
            b.ival = rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = ~rand();
            a.exponent = 0;
            b.ival = rand();
            b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = 0b01111111011111111111111111111111u;
            b.ival = 0b01111111011111111111111111111111u;
            //b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = 0b00000000100000000000000000000001u;
            b.ival = 0b10000000111111111111111111111110u;
            //b.mask();
            Test::testFor(a.fval, b.fval);
        }
        {
            b.ival = rand();
            b.mask();
            a.fval = -b.fval;
            Test::testFor(a.fval, b.fval);
        }
    }
    Test::printTo(cout);
    return 0;
}
