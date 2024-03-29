#pragma once

#include "inputslot.h"
#include "outputslot.h"
#include "connection.h"

#include <QQuickItem>
//base class of all kinds of nodes

namespace NF{

class InputSlot;
class OutputSlot;
class Connection;
class AbstractNodeObject;

class AbstractNode
{
public:
    explicit AbstractNode(): m_dependencyCount(0), m_tag(0) {}
    virtual ~AbstractNode();
    virtual AbstractNode* clone() const = 0;

    virtual void eval() = 0;

    virtual void setValue(int slotIndex, void* ptr) = 0;

    void setObj(AbstractNodeObject* obj) {m_nodeObject = obj;}
    AbstractNodeObject* getObj() const {return m_nodeObject;}

    int getNInput() const {return m_inputSlots.size();}
    int getNOutput() const {return m_outputSlots.size();}

    QString getNameID() const {return m_nodeNameID;}


    void addDepend(int num);
    void decDepend(int num);
    bool independent() const {return m_dependencyCount == 0;}
    int getDependency() const {return m_dependencyCount;}


    InputSlot* getInput(int index) const {return m_inputSlots[index];}
    OutputSlot* getOutput(int index) const {return m_outputSlots[index];}

    void setTag() {m_tag = 1;}
    void clearTag() {m_tag = 0;}
    bool tagged() {return m_tag == 1;}

protected:
    AbstractNodeObject* m_nodeObject;

    std::vector<InputSlot*> m_inputSlots;
    std::vector<OutputSlot*> m_outputSlots;


    //how many unready nodes does this on depend on
    //(it's a graph-level attribute)
    int m_dependencyCount;

    //used for some DFS/BFS traverse algorithms
    int m_tag;

    //global unique id
    QString m_nodeNameID;
};

}

