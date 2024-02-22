#pragma once

#include "Wrapper/slotgettermacro.h"
#include "Wrapper/slotsettermacro.h"
#include "typedefines.h"
#include "typeconversion.h"

namespace Nodest{

REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, QStringSetter, QString)
REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, IntSetter, int)

REGISTER_SLOT_GETTER_CONVERT(Q_OBJECT, QImageGetter, QImage, QString, convertImageToSourceString)

}
