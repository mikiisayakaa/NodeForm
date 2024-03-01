#pragma once

#include "abstractconnectionobject.h"

namespace Nodest{

class TempConnectionObject : public AbstractConnectionObject
{
    Q_OBJECT
public:
    TempConnectionObject(QObject* parent) : AbstractConnectionObject(parent) {}

    ~TempConnectionObject() {}
};

}

