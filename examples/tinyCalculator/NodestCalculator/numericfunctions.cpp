#include "numericfunctions.h"

#include <algorithm>

void Nodest::addInt(const int &a, const int &b, int &c)
{
    c = a + b;
}


void Nodest::intValue(const int &a, int &b)
{
    b = a;
}

void Nodest::multiplyInt(const int &a, const int &b, int &c)
{
    c = a * b;
}

void Nodest::negativeInt(const int &a, int &b)
{
    b = -a;
}

void Nodest::maxInt(const int &a, const int &b, int &c)
{
    c = a > b ? a : b;
}

void Nodest::clampInt(const int &bound1, const int &bound2, const int &a, int &b)
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
