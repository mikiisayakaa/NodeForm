#pragma once

#include <QObject>

#include "abstractslotobject.h"
#include "Core/connection.h"
#include "Global/globaluiparams.h"

namespace NF{

class AbstractConnectionObject;

class SlotObject : public AbstractSlotObject
{
    Q_OBJECT
public:
    explicit SlotObject(AbstractSlot* slot,NF::UIParameters* params, QObject *parent);

    void createWidgets();

    void setWidgetsLayout();

    void setWidgetsLayout2();

    void addExtensions();
signals:

public slots:


protected:
    NF::UIParameters* m_createParams;
};

}
