#pragma once

#include <vector>

namespace Nodest{

void intVector(const std::vector<int>& vec1, std::vector<int>& vec2);

void intVector4D(const int& a, const int& b, const int& c, const int& d,
                 std::vector<int>& vec);

void vectorConcat(const std::vector<int>& vec1, const std::vector<int>& vec2,
                  std::vector<int>& vecRst);

void vectorSort(const std::vector<int>& vec, std::vector<int>& vecRst);

void vectorReverse(const std::vector<int>& vec, std::vector<int>& vecRst);

void vectorSplit(const std::vector<int>& vec, std::vector<int>& vecRst1,
                 std::vector<int>& vecRst2);


}
