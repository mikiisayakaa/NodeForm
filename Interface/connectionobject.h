#pragma once

#include <QObject>
#include <QQuickItem>

#include "abstractconnectionobject.h"
#include "Core/connection.h"
#include "Extension/abstractextension.h"


namespace NF{

class Connection;

class ConnectionObject : public AbstractConnectionObject
{
    Q_OBJECT
public:
    ConnectionObject(QObject* parent = nullptr)
        : AbstractConnectionObject(parent) {}

    ~ConnectionObject() {}

    void addExtensions();

public slots:


private:

};

}
