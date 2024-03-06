#pragma once

#include "Core/basicnodemacro.h"
#include "Core/basicboolnodemacro.h"
#include "vectorfunctions.h"

namespace NF{

BASICNODE(IntVector4DNode, intVector4D, 0)
BASICNODE(VectorDisplayNode, intVector, 1)
BASICNODE(VectorConcatNode, vectorConcat, 2)
BASICNODE(VectorSortNode, vectorSort, 3)
BASICNODE(VectorReverseNode, vectorReverse, 4)
BASICNODE(VectorSplitNode, vectorSplit, 5)

BOOLNODE(VectorPopbackNode, vectorPopback)

}
