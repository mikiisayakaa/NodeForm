#pragma once

namespace Nodest{

enum class ExtensionType{

    //graph level extensions
    GraphNodeSelection,
    GraphConnectionSelection,
    MoveBackground,
    ScaleBackground,
    DeleteSelectedNode,
    DeleteSelectedConnection,

    //node level extensions
    NodeSelection,
    MoveNode,

    //slot level extensions
    DragAddConnection,

    //connection level extensions
    ConnectionSelection,

};

}
