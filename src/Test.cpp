#include "Test.h"

vector<Test> Test::tests = vector<Test> {
    {
        1, "A > 0, B > 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        2, "A > 0, B > 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        3, "A > 0, B > 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        4, "A > 0, B > 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        5, "A < 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        6, "A < 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        7, "A < 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        8, "A < 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        9, "A > 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        10, "A > 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0 && value != INFINITY; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (FloatDump(value).g.order >> 7); }
    },
    {
        11, "A > 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        12, "A > 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(FloatDump(value).g.order >> 7); }
    },
    {
        13, "A = NaN",
        [](float value) { return value != value; },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        14, "A = +infinity",
        [](float value) { return value == INFINITY; },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        15, "A = -infinity",
        [](float value) { return value == -INFINITY; },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        16, "A = +0",
        [](float value) {
            static Float lon;
            //cout << Float(value).ival;
            return true;//Float(value).ival == 0;
        },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        17, "A = -0",
        [](float value) {
            static Float lon = -.0f;
            return Float(value).ival == lon.ival;
        },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        18, "денормализованное A",
        [](float value) { value = abs(value); return value > .0f && value < 0.5f; },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        19, "Y = NaN",
        [](float value) { return true; },
        [](float value) { return true; },
        [](float value) { return value != value; }
    }
};

Test::Test(int id, string s, assertValue a, assertValue b, assertValue y) {
    this->id = id;
    name = s;
    A = a;
    B = b;
    Y = y;
    done = false;
}

bool Test::complited() {
    for (Test & test : tests) {
        if (!test.done)
            return false;
    }
    return true;
}

bool Test::assert(float a, float b) {
    if (A(a) && B(b) && Y(a + b)) {
        aValue = a;
        bValue = b;
        yValue = a + b;
        done = true;
        cout << id << " done!\n";
    }
    return done;
}

void Test::testFor(float a, float b) {
    for (Test & test : tests) {
        if (test.done)
            continue;
        if (test.assert(a, b)) {
            return;
        }
    }
}

void printLastBits(ostream & output, int number, int count) {
    output << "[" << number << "]";
    int mask = 1 << count;
    while (count--) {
        mask >>= 1;
        output << ((number & mask) ? '1' : '0');
    }
}

void Test::printTo(ostream & output) {
    for (Test & test : tests) {
        output << test.id << ": " << test.name << std::endl;
        FloatDump a = test.aValue, b = test.bValue, y = test.yValue;

        output << "\tA = " << test.aValue << "|" << a.ival << " {" << (a.g.sign ? '1' : '0') << '|';
        printLastBits(output, a.g.order, 8);
        output << '|';
        printLastBits(output, a.g.mantisa, 23);
        output << "}\n";
        
        output << "\tB = " << test.bValue << "|" << b.ival << " {" << (b.g.sign ? '1' : '0') << '|';
        printLastBits(output, b.g.order, 8);
        output << '|';
        printLastBits(output, b.g.mantisa, 23);
        output << "}\n";
        
        output << "\tY = " << test.yValue << "|" << y.ival << " {" << (y.g.sign ? '1' : '0') << '|';
        printLastBits(output, y.g.order, 8);
        output << '|';
        printLastBits(output, y.g.mantisa, 23);
        output << "}\n";
    }
}
