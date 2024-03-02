#include "dragaddconnection.h"
#include "Interface/abstractgraphobject.h"
#include "Interface/abstractslotobject.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "Global/globalitems.h"
#include "Interface/tempconnectionobject.h"
#include "Interface/connectionobject.h"
#include "Utils/qmlcreationutils.h"


Nodest::DragAddExtension::DragAddExtension(QObject *parent) :
    AbstractExtension(parent), m_testConnection(nullptr), m_tempConnection(nullptr)
{
    m_extensionName = "DragAddConnection";
    m_type = ExtensionType::DragAddConnection;
}

bool Nodest::DragAddExtension::addExtension(QQuickItem *signalSource)
{
    if (signalSource->property("dummy").isValid()){
        return false;
    }
    connect(signalSource, SIGNAL(connectionEnd(qreal, qreal)), this, SLOT(onConnectionEnd(qreal, qreal)));
    connect(signalSource, SIGNAL(position(qreal, qreal)), this, SLOT(onConnectionDrag(qreal, qreal)));
    m_handle = signalSource;
    return true;
}

void Nodest::DragAddExtension::onConnectionEnd(qreal x, qreal y)
{
    //a single click at the handle will not have any effect
    if (m_testConnection == nullptr){
        return;
    }

    QQuickItem* child = nullptr;
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent()->parent()->parent());
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
            QQuickItem* background = getBackground();
            QQmlComponent* component = NodestGlobal::curveMap[NodestGlobal::globalUI->curveFiles[0]];
            QObject* obj = component->beginCreate(NodestGlobal::engine->rootContext());
            QQuickItem* newLine = qobject_cast<QQuickItem*>(obj);
            QQuickItem* line = m_tempConnection->getItem();
            setLineHandle(line, child);
            newLine->setParentItem(background);

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

void Nodest::DragAddExtension::onConnectionDrag(qreal x, qreal y)
{
    AbstractSlot* slot = dynamic_cast<AbstractSlotObject*>(parent())->getSlot();
    //output slot
    if (slot->getFlow() == 1){
        if (m_testConnection == nullptr){
            m_testConnection = new TestConnection();
            m_testConnection->firstNode = slot->getParent();
            m_testConnection->firstFlow = 1;
            m_testConnection->firstIndex = slot->getIndex();

            connectionStartHelper(m_handle);
        }
        else{
            QQuickItem* line = m_tempConnection->getItem();

            line->setProperty("x2", x);
            line->setProperty("y2", y);
        }
    }
    //input slot
    else{
        if (m_testConnection == nullptr){
            m_testConnection = new TestConnection();
            QQuickItem* line = nullptr;
            QQuickItem* handle = nullptr;

            InputSlot* inSlot = (InputSlot*)slot;

            //already have a connection, we'll cut off the existing one
            if (inSlot->getConnection() != nullptr){
                Connection* oldConnection = inSlot->getConnection();
                OutputSlot* outSlot = oldConnection->getFirst();

                m_testConnection->firstNode = outSlot->getParent();
                m_testConnection->firstFlow = 1;
                m_testConnection->firstIndex = outSlot->getIndex();

                //create before removal, or user will see a flash in the ui
                handle = outSlot->getObj()->getItem(0);

                connectionStartHelper(handle);

                line = m_tempConnection->getItem();
                line->setProperty("x2", m_handle->property("globalX").toReal() +
                                        m_handle->property("width").toReal() / 2);
                line->setProperty("y2", m_handle->property("globalY").toReal() +
                                        m_handle->property("height").toReal() / 2);

                //remove the original connection
                AbstractGraphObject* graphObj = qobject_cast<AbstractGraphObject*>(parent()->parent()->parent());
                graphObj->removeSingleConnection(oldConnection->getObj());

            }
            else{
                handle = m_handle;
                m_testConnection->secondNode = slot->getParent();
                m_testConnection->secondFlow = 0;
                m_testConnection->secondIndex = slot->getIndex();

                connectionStartHelper(m_handle);
            }
        }
        else{
            QQuickItem* line = m_tempConnection->getItem();

            if (m_testConnection->firstNode == nullptr){
                line->setProperty("x1", x);
                line->setProperty("y1", y);
            }
            else{
                line->setProperty("x2", x);
                line->setProperty("y2", y);
            }

        }
    }
}

void Nodest::DragAddExtension::connectionStartHelper(QQuickItem *handle)
{
    QQuickItem* background = getBackground();

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

QQuickItem *Nodest::DragAddExtension::getBackground()
{
    //search along Qt's object tree
    QObject* obj = parent()->parent()->parent();

    return dynamic_cast<AbstractGraphObject*>(obj)->getBackground();
}
