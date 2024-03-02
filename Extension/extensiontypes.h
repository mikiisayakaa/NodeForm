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
    OutDragAddConnection,
    InDragAddConnection,

    //connection level extensions
    ConnectionSelection,

};

}
