#include "Test.h"

static struct {
    float a;
    float b;
} buffer;

// List of the all tests.
vector<Test> Test::tests = vector<Test> {
    {
        1, "A > 0, B > 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        2, "A > 0, B > 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        3, "A > 0, B > 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
    },
    {
        4, "A > 0, B > 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value > 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
    },
    {
        5, "A < 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        6, "A < 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        7, "A < 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
    },
    {
        8, "A < 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value < 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
    },
    {
        9, "A > 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        10, "A > 0, B < 0: Положительный десятичный порядок результата",
        [](float value) { return value > 0 && value != INFINITY; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return (Float(value).exponent >> 7); }
    },
    {
        11, "A > 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
    },
    {
        12, "A > 0, B < 0: Отрицательный десятичный порядок результата",
        [](float value) { return value > 0; },
        [](float value) { return value < 0; },
        [](float value) -> bool { return !(Float(value).exponent >> 7); }
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
            const static Float lon = .0f;
            return Float(value).ival == lon.ival;
        },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        17, "A = -0",
        [](float value) {
            const static Float lon = -.0f;
            return Float(value).ival == lon.ival;
        },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        18, "денормализованное A",
        [](float value) { return Float(value).exponent == 0; },
        [](float value) { return true; },
        [](float value) { return true; }
    },
    {
        19, "Y = NaN",
        [](float value) { return true; },
        [](float value) { return true; },
        [](float value) { return value != value; }
    },
    {
        20, "Y = ovf",
        [](float value) { return value != INFINITY && value != -INFINITY; },
        [](float value) { return value != INFINITY && value != -INFINITY; },
        [](float value) { return value == INFINITY; }
    },
    {   // Deprecated for some reason
        21, "Y = underf",
        [](float value) {
            buffer.a = value;
            //printLastBits(cout, Float(value).ival, 31);
            //cout << '\t';
            return true;
        },
        [](float value) {
            buffer.b = value;
            //printLastBits(cout, Float(value).ival, 31);
            //cout << endl;
            return true;
        },
        [](float value) { return true || abs(value) == .0f && buffer.a != -buffer.b; }
    },
    {
        22, "Y = zero",
        [](float value) { return true; },
        [](float value) { return true; },
        [](float value) { return value == .0f; }
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
        //cout << id << " done!\n";
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
    int mask = 1 << count;
    while (count--) {
        mask >>= 1;
        output << ((number & mask) ? '1' : '0');
    }
}

ostream & operator<<(ostream & output, Float value) {
    output << "{ " << (value.sign ? '1' : '0') << ' ';
        printLastBits(output, value.exponent, 8);
        output << ' ';
        printLastBits(output, value.significand, 23);
        output << " }\t" << value.fval << " | " << value.ival;
}

void Test::printTo(ostream & output) {
    for (Test & test : tests) {
        output << test.id << ": " << test.name << std::endl;
        Float a = test.aValue, b = test.bValue, y = test.yValue;

        output << "\tA = " << a << endl;
        output << "\tB = " << b << endl;
        output << "\tY = " << y << endl;
    }
}
