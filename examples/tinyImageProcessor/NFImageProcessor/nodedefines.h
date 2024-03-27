#pragma once

#include "Core/basicnodemacro.h"
#include "imagefunctions.h"

namespace NF{

BASICNODE(DisplayImageNode, imageDisplay)
BASICNODE(LoadImageNode, loadImage)
BASICNODE(InverseImageNode, inverseImage)
BASICNODE(BrightnessNode, brightness)
BASICNODE(GrayScaleNode, grayScale)

}
