#pragma once

#include <QObject>

namespace NF{
class AbstractNodeObject;
}

class NodeFactory : public QObject
{
    Q_OBJECT
public:
    explicit NodeFactory(QObject *parent = nullptr);

signals:

public slots:
    Q_INVOKABLE void createNode(int index);

    Q_INVOKABLE QString getNodeName(int index);

    Q_INVOKABLE int getNodeNum();

};
