#pragma once

#include "Wrapper/slotgettermacro.h"
#include "Wrapper/slotsettermacro.h"
#include "typedefines.h"
#include "typeconversion.h"

#include <vector>

namespace Nodest{

REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, IntSetter, int)

REGISTER_SLOT_GETTER(Q_OBJECT, IntGetter, int)
REGISTER_SLOT_GETTER_CONVERT(Q_OBJECT, IntVectorGetter, std::vector<int>, QVariantList,
                             IntVectorTOQVariantList)


}
