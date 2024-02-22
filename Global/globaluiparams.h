#pragma once

#include <vector>

#include <QString>
#include <QHash>

namespace NodestGlobal{

struct UIParameters{
    std::vector<std::vector<QString>> inputFiles;
    std::vector<std::vector<QString>> outputFiles;
    QString baseFile;
    QString baseTextFile;

    std::vector<QString> inputNames;
    std::vector<QString> outputNames;

    QString nodeName;
    QString nodeID;
};

//node id to UIparameters
extern QHash<QString, UIParameters*> uiMap;

}
