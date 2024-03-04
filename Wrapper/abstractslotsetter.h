#pragma once

#include <QObject>
#include <QDebug>

namespace NF{

class InputSlot;

class AbstractSlotSetter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSlotSetter(QObject *parent = nullptr) : QObject(parent){}

    virtual ~AbstractSlotSetter() {}

    void setSlot(InputSlot* slot) {m_slot = slot;}

    QString getTypeName() const {return m_typeName;}

signals:
    void updated();


protected:
    InputSlot* m_slot;

    QString m_typeName;

};

}
