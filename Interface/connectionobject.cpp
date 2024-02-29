#include "connectionobject.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"

#include "Extension/extensionfactory.h"


void Nodest::ConnectionObject::addExtension(AbstractExtension *extension)
{

    for (size_t i = 0; i < m_extensions.size(); i++){
        if (m_extensions[i]->getExtensionType() == extension->getExtensionType()){
            return;
        }
    }


    if (extension->addExtension(m_connectionItem)){
        m_extensions.push_back(extension);
    }
    else{
        delete extension;
    }


}

void Nodest::ConnectionObject::addExtensions()
{
    AbstractExtension* ext1 = ExtensionFactory::createExtension(ExtensionType::ConnectionSelection, this);
    addExtension(ext1);
}

