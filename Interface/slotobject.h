#pragma once

#include <QObject>

#include "abstractslotobject.h"
#include "Core/connection.h"

namespace Nodest{

class AbstractConnectionObject;

class SlotObject : public AbstractSlotObject
{
    Q_OBJECT
public:
    explicit SlotObject(AbstractSlot* slot, QObject *parent = nullptr);

    void addExtensions();
signals:

public slots:

protected:

protected:
    TestConnection* m_testConnection;
    AbstractConnectionObject* m_tempConnection;
};

}
