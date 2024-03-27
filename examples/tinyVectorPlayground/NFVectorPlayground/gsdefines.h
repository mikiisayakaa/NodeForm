#pragma once


#include "typedefines.h"
#include "Interface/databridgemacro.h"
#include "typeconversion.h"

#include <vector>

namespace NF{

REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, IntBridge, int)
REGISTER_DATABRIDGE_CONVERT(Q_OBJECT, Q_INVOKABLE, IntVectorBridge,
                            std::vector<int>, QVariantList,
                            IntVectorToQVariantList, QVariantListToIntVector)



}
