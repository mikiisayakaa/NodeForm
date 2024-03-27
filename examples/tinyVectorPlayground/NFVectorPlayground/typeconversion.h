#pragma once

#include <QVariantList>

namespace NF{

QVariantList IntVectorToQVariantList(const std::vector<int>& vec);

std::vector<int> QVariantListToIntVector(const QVariantList& varlist);

}
