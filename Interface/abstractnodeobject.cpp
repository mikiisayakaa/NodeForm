#include "abstractnodeobject.h"

Nodest::AbstractNodeObject::AbstractNodeObject(Nodest::AbstractNode *node, QObject *parent)
    : QObject(parent), m_node(node)
{
    m_node->setObj(this);
}
