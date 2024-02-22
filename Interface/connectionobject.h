#pragma once

#include <QObject>
#include <QQuickItem>

#include "Core/connection.h"

namespace Nodest{

class Connection;

class ConnectionObject : public QObject
{
    Q_OBJECT
public:
    ConnectionObject(QObject* parent = nullptr)
        : QObject(parent), m_connectionItem(nullptr), m_connection(nullptr) {}

    ~ConnectionObject() {}

    void setItem(QQuickItem* connectionItem) {m_connectionItem = connectionItem;}
    QQuickItem* getItem() const {return m_connectionItem;}

    void setConnection(Connection* connection) {m_connection = connection;}
    Connection* getConnection() const {return m_connection;}

public slots:

    //process selection
    void onSelected();

private:

    QQuickItem* m_connectionItem;

    Connection* m_connection;
};

}
