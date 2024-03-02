#include "dragaddconnectionextension.h"

#include "Interface/abstractgraphobject.h"
#include "Global/globalqmlfiles.h"
#include "Global/globaluiparams.h"
#include "Global/globalitems.h"
#include "Interface/connectionobject.h"
#include "Utils/qmlcreationutils.h"


void Nodest::DragAddConnectionExtension::onConnectionEnd(qreal x, qreal y)
{
    if (m_testConnection == nullptr){
        return;
    }

    QQuickItem* child = nullptr;
    AbstractGraphObject* graphObj = dynamic_cast<AbstractGraphObject*>(parent()->parent()->parent());
    for (int i = graphObj->getNNode() - 1; i >= 0; i--){
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
        delete m_line;
        m_line = nullptr;
    }
    else{
        AbstractConnectionObject* connectObj = graphObj->addSingleConnection(m_testConnection);
        if (connectObj == nullptr){
            delete m_line;
            m_line = nullptr;
        }
        else{
            QQuickItem* background = getBackground();
            QQmlComponent* component = NodestGlobal::curveMap[NodestGlobal::globalUI->curveFiles[0]];
            QObject* obj = component->beginCreate(NodestGlobal::engine->rootContext());
            QQuickItem* newLine = qobject_cast<QQuickItem*>(obj);
            setLineHandle(m_line, child);
            newLine->setParentItem(background);

            component->completeCreate();

            setLineHandle(newLine, qvariant_cast<QQuickItem*>(m_line->property("handle1")));
            setLineHandle(newLine, qvariant_cast<QQuickItem*>(m_line->property("handle2")));

            delete m_line;
            m_line = nullptr;

            connectObj->setItem(newLine);
            newLine->setParent(connectObj);

            connectObj->addExtensions();

        }
    }

    delete m_testConnection;
    m_testConnection = nullptr;
}

void Nodest::DragAddConnectionExtension::connectionStartHelper(QQuickItem *handle)
{
    QQuickItem* background = getBackground();

    QQmlComponent* component = NodestGlobal::curveMap[NodestGlobal::globalUI->curveFiles[1]];
    QObject* obj = component->beginCreate(NodestGlobal::engine->rootContext());
    QQuickItem* line = qobject_cast<QQuickItem*>(obj);
    line->setParentItem(background);
    component->completeCreate();

    setLineHandle(line, handle);
    m_line = line;
}

QQuickItem *Nodest::DragAddConnectionExtension::getBackground()
{
    //search along Qt's object tree
    QObject* obj = parent()->parent()->parent();

    return dynamic_cast<AbstractGraphObject*>(obj)->getBackground();
}
