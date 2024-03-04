#include "numericfunctions.h"

#include <algorithm>

void NF::addInt(const int &a, const int &b, int &c)
{
    c = a + b;
}


void NF::intValue(const int &a, int &b)
{
    b = a;
}

void NF::multiplyInt(const int &a, const int &b, int &c)
{
    c = a * b;
}

void NF::negativeInt(const int &a, int &b)
{
    b = -a;
}

void NF::maxInt(const int &a, const int &b, int &c)
{
    c = a > b ? a : b;
}

void NF::clampInt(const int &bound1, const int &bound2, const int &a, int &b)
{
    int b1 = bound1;
    int b2 = bound2;
    if (b1 > b2){
        std::swap(b1, b2);
    }

    if (a < b1){
        b = b1;
    }
    else if (a > b2){
        b = b2;
    }
    else{
        b = a;
    }
}
