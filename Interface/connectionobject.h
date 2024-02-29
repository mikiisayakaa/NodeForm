#pragma once

#include <QObject>
#include <QQuickItem>

#include "abstractconnectionobject.h"
#include "Core/connection.h"
#include "Extension/abstractextension.h"


namespace Nodest{

class Connection;

class ConnectionObject : public AbstractConnectionObject
{
    Q_OBJECT
public:
    ConnectionObject(QObject* parent = nullptr)
        : AbstractConnectionObject(parent) {m_connection = nullptr;
                                            m_connectionItem = nullptr;}

    ~ConnectionObject() {}

    void addExtensions();

public slots:


private:

};

}
