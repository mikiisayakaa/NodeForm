#include "abstractconnectionobject.h"
#include "Extension/abstractextension.h"


void NF::AbstractConnectionObject::addExtension(NF::AbstractExtension *extension)
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
