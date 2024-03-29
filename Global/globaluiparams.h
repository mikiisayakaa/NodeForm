#pragma once

#include <vector>

#include <QString>
#include <QHash>

namespace NF{

struct UIParameters{
    std::vector<std::vector<QString>> inputFiles;
    std::vector<std::vector<QString>> outputFiles;
    std::vector<QString> baseFiles;

    std::vector<QString> inputNames;
    std::vector<QString> outputNames;

    QString nodeName;
    QString nodeID;
};

//node id to UIparameters
extern QHash<QString, UIParameters*> uiMap;

struct GlobalUIParameters{
    std::vector<QString> curveFiles;
    QString backgroundFile;
};

extern GlobalUIParameters* globalUI;

}
