#include "vectorfunctions.h"

#include <algorithm>

#include <QDebug>

void NF::intVector(const std::vector<int> &vec1, std::vector<int> &vec2)
{
    vec2 = vec1;
}


void NF::intVector4D(const int &a, const int &b, const int &c, const int &d, std::vector<int> &vec)
{
    vec.resize(4);
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
    vec[3] = d;
}

void NF::vectorConcat(const std::vector<int> &vec1, const std::vector<int> &vec2, std::vector<int> &vecRst)
{
    vecRst = vec1;
    vecRst.insert(vecRst.end(), vec2.begin(), vec2.end());
}

void NF::vectorSort(const std::vector<int> &vec, std::vector<int> &vecRst)
{
    vecRst = vec;
    std::sort(vecRst.begin(), vecRst.end());
}

void NF::vectorReverse(const std::vector<int> &vec, std::vector<int> &vecRst)
{
    vecRst = vec;
    std::reverse(vecRst.begin(), vecRst.end());
}

void NF::vectorSplit(const std::vector<int> &vec, std::vector<int> &vecRst1, std::vector<int> &vecRst2)
{
    vecRst1.clear();
    vecRst1.insert(vecRst1.end(), vec.begin(), vec.begin() + vec.size() / 2);
    vecRst2.clear();
    vecRst2.insert(vecRst2.end(), vec.begin() + vec.size() / 2, vec.end());
}


bool NF::vectorPopback(const std::vector<int> &vec, std::vector<int> &vecRst, int& value)
{
    if (vec.empty()){
        qDebug() << "error happened";
        return false;
    }

    vecRst = vec;
    value = vecRst.back();
    vecRst.pop_back();

    return true;
}
