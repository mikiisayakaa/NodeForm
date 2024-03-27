#include "typeconversion.h"

QVariantList NF::IntVectorToQVariantList(const std::vector<int> &vec)
{
    QVariantList list;
    list.reserve(vec.size());

    for (size_t i = 0; i < vec.size(); i++){
        list.push_back(vec[i]);
    }

    return list;
}

//not used
std::vector<int> NF::QVariantListToIntVector(const QVariantList &varlist)
{
    return std::vector<int>();
}
