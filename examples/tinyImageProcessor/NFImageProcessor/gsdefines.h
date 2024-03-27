#pragma once

#include "typedefines.h"
#include "Interface/databridgemacro.h"

#include "typeconversion.h"

namespace NF{

REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, QStringBridge, QString)
REGISTER_DATABRIDGE(Q_OBJECT, Q_INVOKABLE, IntBridge, int)

REGISTER_DATABRIDGE_CONVERT(Q_OBJECT, Q_INVOKABLE, QImageQStringBridge,
                            QImage, QString, convertImageToSourceString,
                            convertSourceStringToImage)


}
