
#ifndef __TEST_HEAD__
#define __TEST_HEAD__

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

union Float {
    float fval;
    struct {
        unsigned int mantisa : 23;
        unsigned int order : 8;
        unsigned int sign : 1;
    } g;
    int ival;

    Float(float value) {
        fval = value;
        
    }

    Float() {}
};

void printLastBits(ostream & output, int number, int count);

typedef Float FloatDump;

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