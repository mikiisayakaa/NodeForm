#include "qmlcreationutils.h"
#include "Global/globalqmlfiles.h"
#include "Global/globalitems.h"
#include "Core/inputslot.h"
#include "Core/outputslot.h"
#include "Interface/abstractdatabridge.h"

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

void NF::createDummy(QQuickItem *parentItem, QQuickItem *&target)
{
    QObject* obj;
    QQmlComponent* component = NF::dummy;
    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    component->completeCreate();
}

void NF::createDataBridge(const QString &fileName, QQuickItem *parentItem, QQuickItem *&target, AbstractDataBridge *dataBridge, int flow)
{
    QObject* obj = nullptr;
    QQmlComponent* component = flow == 0 ? NF::dataBridgeSetterMap[fileName].data :
                                           NF::dataBridgeGetterMap[fileName].data;

    obj = component->beginCreate(NF::engine->rootContext());

    target = qobject_cast<QQuickItem*>(obj);
    target->setParentItem(parentItem);

    dataBridge->setItem(target);
    dataBridge->bind();

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

void NF::getValidDataBridgeFileName(QString &queryName, NF::AbstractSlot *slot)
{
    if (queryName == NF::dummyFile){
        return;
    }

    if (slot->getFlow() == 0 && NF::dataBridgeSetterMap.contains(queryName)){
        QString cppType = NF::dataBridgeSetterMap[queryName].cppTypeName;
        if (cppType == slot->getTypeName()){
            //slot type problem here, fix this later
            return;
        }
    }
    else if (slot->getFlow() == 1 && NF::dataBridgeGetterMap.contains(queryName)){
        QString cppType = NF::dataBridgeGetterMap[queryName].cppTypeName;
        if (cppType == slot->getTypeName()){
            return;
        }
    }

    //check default list
    if (slot->getFlow() == 0){
        for (auto& filename : NF::dataBridgeSetterDefault){
            if (NF::dataBridgeSetterMap[filename].cppTypeName == slot->getTypeName()){
                queryName = filename;
                return;
            }
        }
    }
    else if (slot->getFlow() == 1){
        for (auto& filename : NF::dataBridgeGetterDefault){
            if (NF::dataBridgeGetterMap[filename].cppTypeName == slot->getTypeName()){
                queryName = filename;
                return;
            }
        }
    }


    queryName = NF::dummyFile;
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





