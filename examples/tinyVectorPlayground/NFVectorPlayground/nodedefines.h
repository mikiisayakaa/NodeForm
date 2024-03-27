#pragma once

#include "Core/basicnodemacro.h"
#include "Core/basicboolnodemacro.h"
#include "vectorfunctions.h"

namespace NF{

BASICNODE(VectorDisplayNode, intVector)
BASICNODE(IntVector4DNode, intVector4D)
BASICNODE(VectorConcatNode, vectorConcat)
BASICNODE(VectorSortNode, vectorSort)
BASICNODE(VectorReverseNode, vectorReverse)
BASICNODE(VectorSplitNode, vectorSplit)

BOOLNODE(VectorPopbackNode, vectorPopback)

}
