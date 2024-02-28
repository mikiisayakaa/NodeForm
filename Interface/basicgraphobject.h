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

    void addExtensions();



public slots:
//    void onDeletePressed();

//    void onPreCopy();

//    void onCopy();

private:

    std::vector<AbstractNodeObject*> m_nodeObjectsToCopy;
};

}

