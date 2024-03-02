#pragma once

#include <QObject>

#include "abstractslotobject.h"
#include "Core/connection.h"
#include "Global/globaluiparams.h"

namespace Nodest{

class AbstractConnectionObject;

class SlotObject : public AbstractSlotObject
{
    Q_OBJECT
public:
    explicit SlotObject(AbstractSlot* slot,NodestGlobal::UIParameters* params, QObject *parent);

    void createWidgets();

    void setWidgetsLayout();

    void addExtensions();
signals:

public slots:


protected:
    NodestGlobal::UIParameters* m_createParams;
    TestConnection* m_testConnection;
    AbstractConnectionObject* m_tempConnection;
};

}
