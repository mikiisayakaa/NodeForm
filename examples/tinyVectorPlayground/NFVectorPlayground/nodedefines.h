#pragma once

#include "Core/basicnodemacro.h"
#include "Core/basicboolnodemacro.h"
#include "vectorfunctions.h"

namespace NF{

BASICNODE(IntVector4DNode, intVector4D)
BASICNODE(VectorDisplayNode, intVector)
BASICNODE(VectorConcatNode, vectorConcat)
BASICNODE(VectorSortNode, vectorSort)
BASICNODE(VectorReverseNode, vectorReverse)
BASICNODE(VectorSplitNode, vectorSplit)

BOOLNODE(VectorPopbackNode, vectorPopback)

}
