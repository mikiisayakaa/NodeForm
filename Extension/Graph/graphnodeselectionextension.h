#pragma once

#include <QObject>

#include <vector>

#include "Extension/abstractextension.h"

namespace Nodest{

class AbstractNodeObject;

//enable node selection
class GraphNodeSelectionExtension : public AbstractExtension
{
    Q_OBJECT
public:
    GraphNodeSelectionExtension(QObject* parent) :
        AbstractExtension(parent) { m_extensionName = "GraphNodeSelection";
                                    m_type = ExtensionType::GraphNodeSelection;}

    bool addExtension(QQuickItem* signalSource);

    void selectOne(AbstractNodeObject* nodeObj);

    void deselectOne(AbstractNodeObject* nodeObj);



public slots:

    void onDeselect();


private:
    std::vector<AbstractNodeObject*> m_selectedNodes;

};

}

