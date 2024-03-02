#include "extensionfactory.h"

#include "extensiontypes.h"

#include "Extension/Graph/graphconnectionselectionextension.h"
#include "Extension/Graph/graphnodeselectionextension.h"
#include "Extension/Graph/movebackgroundextension.h"
#include "Extension/Graph/scalebackgroundextension.h"
#include "Extension/Graph/deleteselectednodeextension.h"
#include "Extension/Graph/deleteselectedconnecitonextension.h"
#include "Extension/Node/nodeselectionextension.h"
#include "Extension/Node/movenodeextension.h"
#include "Extension/Connection/connectionselectionextension.h"
#include "Extension/Slot/dragaddconnection.h"

Nodest::AbstractExtension *Nodest::ExtensionFactory::createExtension(Nodest::ExtensionType type, QObject *parent)
{
    switch(type){

    case ExtensionType::GraphConnectionSelection:
        return new GraphConnectionSelectionExtension(parent);

    case ExtensionType::GraphNodeSelection:
        return new GraphNodeSelectionExtension(parent);

    case ExtensionType::MoveBackground:
        return new MoveBackgroundExtension(parent);

    case ExtensionType::ScaleBackground:
        return new ScaleBackgroundExtension(parent);

    case ExtensionType::DeleteSelectedNode:
        return new DeleteSelectedNodeExtension(parent);

    case ExtensionType::DeleteSelectedConnection:
        return new DeleteSelectedConnecitonExtension(parent);

    case ExtensionType::NodeSelection:
        return new NodeSelectionExtension(parent);

    case ExtensionType::MoveNode:
        return new MoveNodeExtension(parent);

    case ExtensionType::ConnectionSelection:
        return new ConnectionSelectionExtension(parent);

    case ExtensionType::DragAddConnection:
        return new DragAddExtension(parent);

    default:
        break;
    }

    return nullptr;
}
