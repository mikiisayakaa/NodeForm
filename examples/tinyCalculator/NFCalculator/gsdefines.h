#pragma once

#include "Wrapper/slotgettermacro.h"
#include "Wrapper/slotsettermacro.h"
#include "typedefines.h"

namespace NF{

REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, IntSetter, int)
REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, DoubleSetter, double)

REGISTER_SLOT_GETTER(Q_OBJECT, IntGetter, int)

}
