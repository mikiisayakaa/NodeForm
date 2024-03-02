#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/outputslot.h"
#include "Global/globaluiparams.h"
#include "Core/connection.h"
#include "connectionobject.h"
#include "slotobject.h"

namespace Nodest{

class OutputSlotObject : public SlotObject
{
    Q_OBJECT
public:
    explicit OutputSlotObject(OutputSlot* slot, NodestGlobal::UIParameters* params, QObject *parent);

    ~OutputSlotObject();

    void createWidgets();

    void setWidgetsLayout();

signals:

public slots:

private:
    NodestGlobal::UIParameters* m_createParams;


};

}

