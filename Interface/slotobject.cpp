#include "slotobject.h"
#include "Global/globalitems.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "connectionobject.h"
#include "tempconnectionobject.h"
#include "Utils/qmlcreationutils.h"
#include "abstractgraphobject.h"
#include "Extension/extensionfactory.h"

Nodest::SlotObject::SlotObject(Nodest::AbstractSlot *slot, QObject *parent)
    :AbstractSlotObject (slot, parent), m_testConnection(nullptr), m_tempConnection(nullptr)
{

}

void Nodest::SlotObject::bindWidgets()
{
//    if (m_items[0]->property("dummy").isValid()){
//        return;
//    }

    //connect(m_items[0], SIGNAL(connectionEnd(qreal, qreal)), this, SLOT(onConnectionEnd(qreal, qreal)));
    //connect(m_items[0], SIGNAL(position(qreal, qreal)), this, SLOT(onConnectionDrag(qreal, qreal)));
}

void Nodest::SlotObject::addExtensions()
{
    std::vector<ExtensionType> extensionList{
        ExtensionType::DragAddConnection
    };

    for (auto& type : extensionList){
        AbstractExtension* extension = ExtensionFactory::createExtension(type, this);
        addExtension(extension);
    }
}




void Nodest::SlotObject::onConnectionEnd(qreal x, qreal y)
{
    //a single click at the handle will not have any effect
    if (m_testConnection == nullptr){
        return;
    }

    QQuickItem* child = nullptr;
    AbstractGraphObject* graphObj = qobject_cast<AbstractGraphObject*>(NodestGlobal::globalBackground->parent());
    for (int i = graphObj->getNNodes() - 1; i >= 0; i--){
        AbstractNodeObject* nodeObj = graphObj->getNodeObject(i);
        QQuickItem* nodeBase = nodeObj->getNodeBase();

        //get local coordinate of the current baseItem
        child = nodeBase->childAt((x - nodeBase->property("x").toReal()),
                                  (y - nodeBase->property("y").toReal()));

        //we have find a handle, only handles have flow property
        if (child && child->property("flow").isValid()){
            if (m_testConnection->secondNode == nullptr){
                m_testConnection->secondNode = nodeObj->getNode();
                m_testConnection->secondFlow = child->property("flow").toInt();
                m_testConnection->secondIndex = child->property("index").toInt();
                break;
            }

            if (m_testConnection->firstNode == nullptr){
                m_testConnection->firstNode = nodeObj->getNode();
                m_testConnection->firstFlow = child->property("flow").toInt();
                m_testConnection->firstIndex = child->property("index").toInt();
                break;
            }
        }

    }


    if (m_testConnection->secondNode == nullptr || m_testConnection->firstNode == nullptr){
        delete m_tempConnection;
    }
    else{
        Connection* connection = graphObj->addSingleConnection(m_testConnection);
        if (connection == nullptr){
            delete m_tempConnection;
        }
        else{
            QQuickItem* background = NodestGlobal::globalBackground;
            QQmlComponent* component = NodestGlobal::curveMap[NodestGlobal::globalUI->curveFiles[0]];
            QObject* obj = component->beginCreate(NodestGlobal::engine->rootContext());
            QQuickItem* newLine = qobject_cast<QQuickItem*>(obj);
            QQuickItem* line = m_tempConnection->getItem();
            setLineHandle(line, child);
            newLine->setParentItem(background);

            //qDebug() << qvariant_cast<QQuickItem*>(line->property("handle1")) << qvariant_cast<QQuickItem*>(line->property("handle2"));
            component->completeCreate();

            setLineHandle(newLine, qvariant_cast<QQuickItem*>(line->property("handle1")));
            setLineHandle(newLine, qvariant_cast<QQuickItem*>(line->property("handle2")));

            delete m_tempConnection;
            m_tempConnection = new ConnectionObject(background->parent());
            m_tempConnection->setItem(newLine);


            connection->setObj(m_tempConnection);
            m_tempConnection->setConnection(connection);
            m_tempConnection->addExtensions();

        }
    }

    delete m_testConnection;
    m_testConnection = nullptr;
}

void Nodest::SlotObject::connectionStartHelper(QQuickItem *handle)
{
    QQuickItem* background = NodestGlobal::globalBackground;

    QQmlComponent* component = NodestGlobal::curveMap[NodestGlobal::globalUI->curveFiles[1]];
    QObject* obj = component->beginCreate(NodestGlobal::engine->rootContext());
    QQuickItem* line = qobject_cast<QQuickItem*>(obj);
    line->setParentItem(background);
    component->completeCreate();

    setLineHandle(line, handle);


    m_tempConnection = new TempConnectionObject(background->parent());
    m_tempConnection->setItem(line);
    line->setParent(m_tempConnection);

}




