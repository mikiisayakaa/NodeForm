#pragma once

#include "Core/basicnodemacro.h"
#include "numericfunctions.h"


namespace NF{

BASICNODE(IntNode, intValue, 0)
BASICNODE(AddIntNode, addInt, 1)
BASICNODE(MultiplyIntNode, multiplyInt, 2)
BASICNODE(MaxIntNode, maxInt, 3)
BASICNODE(NegativeIntNode, negativeInt, 4)
BASICNODE(ClampIntNode, clampInt, 5)

}
