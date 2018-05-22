
#ifndef __TEST_HEAD__
#define __TEST_HEAD__

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cinttypes>

using namespace std;

union Float;

void printLastBits(ostream & output, int number, int count);
ostream & operator<<(ostream & output, Float value);

// Float union that describes IEEE 754
union Float {
    float fval;
    struct {
        uint32_t significand : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    };
    uint32_t ival;

    Float(float value) {
        fval = value;
    }

    Float(uint32_t value) {
        ival = value;
    }

    Float() {}

    void mask();

    friend ostream & operator<<(ostream & output, Float value);
};

class Test {
public:
    typedef bool(*assertValue)(float value);
    static vector<Test> tests;

private:
    int id;
    bool done;
    float aValue, bValue, yValue;
    string name;
    assertValue A;
    assertValue B;
    assertValue Y;

    Test(int id, string s, assertValue a, assertValue b, assertValue y);

public:
    static bool complited();

    static void testFor(float a, float b);

    bool assert(float a, float b);

    static void printTo(ostream & output);
};

#endif // __TEST_HEAD__