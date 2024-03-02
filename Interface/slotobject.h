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

    void bindWidgets();

    void addExtensions();
signals:

public slots:
    void onConnectionEnd(qreal x, qreal y);

protected:
    void connectionStartHelper(QQuickItem* handle);



protected:
    TestConnection* m_testConnection;
    AbstractConnectionObject* m_tempConnection;
};

}
