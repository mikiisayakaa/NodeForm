#pragma once

#include "abstractslotsetter.h"
#include "abstractslotgetter.h"
#include "Core/abstractnode.h"
#include "slotsettermacro.h"
#include "slotgettermacro.h"
#include "Global/typenamemacro.h"
#include "TypeConvertFuncs/typeconversions.h"

#include <QObject>

//register setters
namespace Nodest{

//REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, IntSlotSetter, int)
//REGISTER_SLOT_SETTER(Q_OBJECT, Q_INVOKABLE, DoubleSlotSetter, double)
//REGISTER_SLOT_SETTER_CONVERT(Q_OBJECT, Q_INVOKABLE, FloatSlotSetter, float, double, doubleToFloat)

}

//register getters
namespace Nodest{

//REGISTER_SLOT_GETTER(Q_OBJECT, IntSlotGetter, int)

}
