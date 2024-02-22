#pragma once

#include <QObject>

#include "abstractgraphobject.h"

namespace Nodest{

class BasicGraphObject : public AbstractGraphObject
{
    Q_OBJECT
public:
    BasicGraphObject(AbstractNodeGraph* graph, QObject* parent = nullptr);

    void createWidgets();

    void bindWidgets();

    //methods about selections
    void clearNodeSelection();

    void clearConnectionSelection();

    auto& getSelectedNodes() {return m_selectedNodeObjects;}

    auto& getSelectedConnects() {return m_selectedConnectObjects;}

public slots:
    void onBgdClicked();

    void onDeletePressed();

    void onPreCopy();

    void onCopy();

private:
    std::vector<ConnectionObject*> m_selectedConnectObjects;
    std::vector<AbstractNodeObject*> m_selectedNodeObjects;

    std::vector<AbstractNodeObject*> m_nodeObjectsToCopy;
};

}

