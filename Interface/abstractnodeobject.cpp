#include "abstractnodeobject.h"
#include "Extension/abstractextension.h"

Nodest::AbstractNodeObject::AbstractNodeObject(Nodest::AbstractNode *node, QObject *parent)
    : QObject(parent), m_node(node)
{
    m_node->setObj(this);
}

void Nodest::AbstractNodeObject::addExtension(Nodest::AbstractExtension *extension)
{
    for (size_t i = 0; i < m_extensions.size(); i++){
        if (m_extensions[i]->getExtensionType() == extension->getExtensionType()){
            return;
        }
    }


    if (extension->addExtension(m_nodeBase)){
        m_extensions.push_back(extension);
    }
    else{
        delete extension;
    }
}
