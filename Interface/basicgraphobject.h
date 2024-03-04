#pragma once

#include <QObject>

#include "abstractgraphobject.h"

namespace NF{

class BasicGraphObject : public AbstractGraphObject
{
    Q_OBJECT
public:
    BasicGraphObject(AbstractNodeGraph* graph, QObject* parent = nullptr);

    void createWidgets();

    void addExtensions();



public slots:

//    void onPreCopy();

//    void onCopy();

private:

    std::vector<AbstractNodeObject*> m_nodeObjectsToCopy;
};

}

