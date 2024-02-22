#include "qmlcreationutils.h"
#include "Global/globalqmlfiles.h"
#include "Global/globalitems.h"
#include "Core/inputslot.h"
#include "Core/outputslot.h"

void Nodest::createTextLabel(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, const QString &text)
{
    QObject* obj;
    QQmlComponent* component = NodestGlobal::textLabelMap[fileName];
    obj = component->beginCreate(NodestGlobal::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setProperty("text", text);
    target->setParentItem(parentItem);

    component->completeCreate();
}


void Nodest::createHandle(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, AbstractSlot* slot)
{
    QObject* obj;
    QQmlComponent* component = NodestGlobal::slotHandleMap[fileName];
    obj = component->beginCreate(NodestGlobal::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    target->setProperty("flow", slot->getFlow());
    target->setProperty("index", slot->getIndex());

    component->completeCreate();
}

void Nodest::createSetter(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, Nodest::AbstractSlot *slot)
{
    QObject* obj = nullptr;
    QQmlComponent* component = nullptr;

    component = NodestGlobal::slotSetterMap[fileName].data;
    obj = component->beginCreate(NodestGlobal::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    //we have to do binding before creation complete,
    //or the init value of the slot will not be correctly set
    slot->getParent()->bindSetter(target, slot->getIndex());

    component->completeCreate();
}

void Nodest::createGetter(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, OutputSlot *slot)
{
    QObject* obj = nullptr;
    QQmlComponent* component = NodestGlobal::slotGetterMap[fileName].data;

    obj = component->beginCreate(NodestGlobal::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    if (slot->getGetter() != nullptr){
        slot->getGetter()->setItem(target);
    }

    component->completeCreate();
}

void Nodest::createBase(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target)
{
    QObject* obj;
    QQmlComponent* component = NodestGlobal::nodeBaseMap[fileName];
    obj = component->beginCreate(NodestGlobal::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    //place it at the center of the window
    target->setProperty("x", parentItem->width() / 2 + NodestGlobal::globalRootObject->width() / 2);
    target->setProperty("y", parentItem->height() / 2 + NodestGlobal::globalRootObject->height() / 2);    
    component->completeCreate();

}

void Nodest::getValidSetterFileName(QString &queryName, InputSlot *slot)
{
    if (slot->getSetter() == nullptr){
        queryName = NodestGlobal::dummyFile;
        return;
    }

    if (queryName == NodestGlobal::dummyFile){
        delete slot->getSetter();
        slot->setSetter(nullptr);
        slot->getParent()->addDepend(1);
        return;
    }

    if (NodestGlobal::slotSetterMap.contains(queryName) &&
            NodestGlobal::slotSetterMap[queryName].typeName == slot->getSetter()->getTypeName()){
        return;
    }

    for (auto& fileName: NodestGlobal::slotSetterDefault){
        if (NodestGlobal::slotSetterMap[fileName].typeName == slot->getSetter()->getTypeName()){
            queryName = fileName;
            return;
        }
    }

    queryName = NodestGlobal::dummyFile;
    delete slot->getSetter();
    slot->setSetter(nullptr);
    slot->getParent()->addDepend(1);

}

void Nodest::getValidGetterFileName(QString &queryName, Nodest::OutputSlot *slot)
{
    if (slot->getGetter() == nullptr){
        queryName = NodestGlobal::dummyFile;
        return;
    }

    if (queryName == NodestGlobal::dummyFile){
        delete slot->getGetter();
        slot->setGetter(nullptr);
        return;
    }

    if (NodestGlobal::slotGetterMap.contains(queryName) &&
            NodestGlobal::slotGetterMap[queryName].typeName == slot->getGetter()->getTypeName()){
        return;
    }

    for (auto& fileName: NodestGlobal::slotGetterDefault){
        if (NodestGlobal::slotGetterMap[fileName].typeName == slot->getGetter()->getTypeName()){
            queryName = fileName;
            return;
        }
    }

    queryName = NodestGlobal::dummyFile;
    delete slot->getGetter();
    slot->setGetter(nullptr);
}


void Nodest::setLinePoint(QQuickItem *line, QQuickItem *handle)
{
    QQuickItem* nodeBase = handle->parentItem();
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


void Nodest::setAnchors(QQuickItem *target, QQuickItem *source, const char *pos1, const char *pos2)
{
    qvariant_cast<QObject*>(target->property("anchors"))->setProperty(pos1,
           source->property(pos2));
}
