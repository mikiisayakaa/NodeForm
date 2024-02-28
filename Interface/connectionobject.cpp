#include "connectionobject.h"
#include "abstractgraphobject.h"
#include "basicgraphobject.h"

#include "Extension/Connection/connectionselectionextension.h"


void Nodest::ConnectionObject::addExtension(AbstractExtension *extension)
{

    for (size_t i = 0; i < m_extensions.size(); i++){
        if (m_extensions[i]->getExtensionName() == extension->getExtensionName()){
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
    ConnectionSelectionExtension* ext1 = new ConnectionSelectionExtension(this);
    addExtension(ext1);
}

