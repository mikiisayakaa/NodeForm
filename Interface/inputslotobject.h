#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/inputslot.h"
#include "Global/globaluiparams.h"
#include "connectionobject.h"
#include "Core/connection.h"
#include "slotobject.h"

namespace Nodest{

class InputSlotObject : public SlotObject
{
    Q_OBJECT
public:
    explicit InputSlotObject(InputSlot* slot,NodestGlobal::UIParameters* params, QObject *parent);

    ~InputSlotObject() {}

    void createWidgets();

    void setWidgetsLayout();
signals:

public slots:

private:
    NodestGlobal::UIParameters* m_createParams;

};

}
