#pragma once

#include <QObject>

class NodeFactoryVector : public QObject
{
    Q_OBJECT
public:
    explicit NodeFactoryVector(QObject *parent = nullptr);

signals:

public slots:    
    Q_INVOKABLE void createNode(int index);
};
