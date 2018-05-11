#include <iostream>
#include <string>
#include <climits>
#include <cmath>

#include "Test.h"

int p_mask = 0;
int n_mask = 1;

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
    cout << "Введите битовую маску мантиссы B: ";
    cin >> mantissa;
    if (mantissa.length() != 23)
        return inputError();
    checkString(mantissa);
    cout << "Введите битовую маску порядка B: ";
    cin >> order;
    if (order.length() != 8)
        return inputError();
    checkString(order);

    fillMask(order);
    fillMask(mantissa);
    /*
    cout << "Mask: ";
    printLastBits(cout, p_mask >> 16, 16);
    printLastBits(cout, p_mask, 16);
    cout << " ";
    printLastBits(cout, n_mask >> 16, 16);
    printLastBits(cout, n_mask >> 16, 16);
    cout << endl;
    */

    while (!Test::complited()) {
        Float a;
        Float b;
        {
            a.ival = rand();
            b.ival = rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = rand();
            b.ival = ~rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = ~rand();
            b.ival = ~rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        // Special cases
        {
            a.fval = NAN;
            b.ival = rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = INFINITY;
            b.ival = ~rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = -INFINITY;
            b.ival = rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.ival = 0;
            b.ival = ~rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
        {
            a.fval = -.0f;
            b.ival = rand();
            b.ival &= n_mask;
            b.ival |= p_mask;
            Test::testFor(a.fval, b.fval);
        }
    }
    Test::printTo(cout);
    return 0;
}
// xxxxxxxxxxxxxxxxxxx1xxx x0x0xxxx