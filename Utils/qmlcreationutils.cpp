#include "qmlcreationutils.h"
#include "Global/globalqmlfiles.h"
#include "Global/globalitems.h"
#include "Core/inputslot.h"
#include "Core/outputslot.h"

void NF::createTextLabel(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, const QString &text)
{
    QObject* obj;
    QQmlComponent* component = NF::textLabelMap[fileName];
    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setProperty("text", text);
    target->setParentItem(parentItem);

    component->completeCreate();
}


void NF::createHandle(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, AbstractSlot* slot)
{
    QObject* obj;
    QQmlComponent* component = NF::slotHandleMap[fileName];
    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    target->setProperty("flow", slot->getFlow());
    target->setProperty("index", slot->getIndex());

    component->completeCreate();
}

void NF::createSetter(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, NF::AbstractSlot *slot)
{
    QObject* obj = nullptr;
    QQmlComponent* component = nullptr;

    component = NF::slotSetterMap[fileName].data;
    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    //we have to do binding before creation complete,
    //or the init value of the slot will not be correctly set
    slot->getParent()->bindSetter(target, slot->getIndex());

    component->completeCreate();
}

void NF::createGetter(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, AbstractSlot *slot)
{
    QObject* obj = nullptr;
    QQmlComponent* component = NF::slotGetterMap[fileName].data;

    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    if (((OutputSlot*)slot)->getGetter() != nullptr){
        ((OutputSlot*)slot)->getGetter()->setItem(target);
    }

    component->completeCreate();
}

void NF::createBase(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target)
{
    QObject* obj;
    QQmlComponent* component = NF::nodeBaseMap[fileName];
    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    //place it at the center of the window
    target->setProperty("x", parentItem->width() / 2 + NF::globalRootObject->width() / 2);
    target->setProperty("y", parentItem->height() / 2 + NF::globalRootObject->height() / 2);    
    component->completeCreate();

}

void NF::getValidSetterFileName(QString &queryName, InputSlot *slot)
{

    if (slot->getSetter() == nullptr){
        queryName = NF::dummyFile;
        return;
    }

    if (queryName == NF::dummyFile){
        delete slot->getSetter();
        slot->setSetter(nullptr);
        slot->getParent()->addDepend(1);
        return;
    }

    if (NF::slotSetterMap.contains(queryName) &&
            NF::slotSetterMap[queryName].typeName == slot->getSetter()->getTypeName()){
        return;
    }

    for (auto& fileName: NF::slotSetterDefault){
        if (NF::slotSetterMap[fileName].typeName == slot->getSetter()->getTypeName()){
            queryName = fileName;
            return;
        }
    }

    queryName = NF::dummyFile;
    delete slot->getSetter();
    slot->setSetter(nullptr);
    slot->getParent()->addDepend(1);

}

void NF::getValidGetterFileName(QString &queryName, NF::OutputSlot *slot)
{
    if (slot->getGetter() == nullptr){
        queryName = NF::dummyFile;
        return;
    }

    if (queryName == NF::dummyFile){
        delete slot->getGetter();
        slot->setGetter(nullptr);
        return;
    }

    if (NF::slotGetterMap.contains(queryName) &&
            NF::slotGetterMap[queryName].typeName == slot->getGetter()->getTypeName()){
        return;
    }

    for (auto& fileName: NF::slotGetterDefault){
        if (NF::slotGetterMap[fileName].typeName == slot->getGetter()->getTypeName()){
            queryName = fileName;
            return;
        }
    }

    queryName = NF::dummyFile;
    delete slot->getGetter();
    slot->setGetter(nullptr);
}


void NF::setLineHandle(QQuickItem *line, QQuickItem *handle)
{
    int flow = handle->property("flow").toInt();

    if (flow == 1){
        line->setProperty("handle1", QVariant::fromValue<QObject*>(handle));

        if (line->property("handle2").isNull()){
            line->setProperty("x2", line->property("x1"));
            line->setProperty("y2", line->property("y1"));
        }
    }
    else{

        line->setProperty("handle2", QVariant::fromValue<QObject*>(handle));

        if (line->property("handle1").isNull()){
            line->setProperty("x1", line->property("x2"));
            line->setProperty("y1", line->property("y2"));

        }
    }
}


void NF::setAnchors(QQuickItem *target, QQuickItem *source, const char *pos1, const char *pos2)
{
    qvariant_cast<QObject*>(target->property("anchors"))->setProperty(pos1,
           source->property(pos2));
}
