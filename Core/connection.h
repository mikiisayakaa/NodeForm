#pragma once

#include "Interface/abstractconnectionobject.h"

namespace NF{

class InputSlot;
class OutputSlot;

class AbstractConnectionObject;

class Connection
{

public:
    explicit Connection(OutputSlot* first, InputSlot* second)
        : m_first(first), m_second(second)  {}

    ~Connection();

    OutputSlot* getFirst() {return m_first;}
    InputSlot* getSecond() {return m_second;}

    void setObj(AbstractConnectionObject* obj) {m_connectObj = obj;}
    AbstractConnectionObject* getObj() const {return m_connectObj;}

private:
    //a little confusing here: m_first is the start of the flow,
    //m_second is the end of the flow
    OutputSlot* m_first;
    InputSlot* m_second;

    AbstractConnectionObject* m_connectObj;

};

class AbstractNode;

struct TestConnection
{
public:
    TestConnection(AbstractNode* firstNode, int firstIndex, int firstFlow,
                            AbstractNode* secondNode, int secondIndex, int secondFlow)
        : firstNode(firstNode), secondNode(secondNode), firstIndex(firstIndex),
          secondIndex(secondIndex), firstFlow(firstFlow), secondFlow(secondFlow)
    {}

    TestConnection() : firstNode(nullptr), secondNode(nullptr) {}

public:
    AbstractNode* firstNode;
    AbstractNode* secondNode;
    int firstFlow;
    int secondFlow;
    int firstIndex;
    int secondIndex;
};

}

