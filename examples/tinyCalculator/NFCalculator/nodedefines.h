#pragma once

#include "Core/basicnodemacro.h"
#include "numericfunctions.h"


namespace NF{

BASICNODE(IntNode, intValue)
BASICNODE(AddIntNode, addInt)
BASICNODE(MultiplyIntNode, multiplyInt)
BASICNODE(MaxIntNode, maxInt)
BASICNODE(NegativeIntNode, negativeInt)
BASICNODE(ClampIntNode, clampInt)

}
