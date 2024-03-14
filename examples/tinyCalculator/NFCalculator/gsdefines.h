#pragma once


#include "typedefines.h"
#include "Interface/databridgemacro.h"

namespace NF{

REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, IntToIntBridge, int)
REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, DoubleToDoubleBridge, double)

}
