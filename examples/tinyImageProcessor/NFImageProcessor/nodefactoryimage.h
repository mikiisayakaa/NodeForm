#pragma once

#include <QObject>

class NodeFactoryImage : public QObject
{
    Q_OBJECT
public:
    explicit NodeFactoryImage(QObject *parent = nullptr);

signals:

public slots:
    Q_INVOKABLE void createNode(int index);
};
