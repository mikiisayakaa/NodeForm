#include "fileoperations.h"
#include "Global/globalpaths.h"
#include "Global/globalqmlfiles.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

NodestGlobal::UIParameters* Nodest::loadUIJson(const QString &jsonPath)
{
    QString absDir = jsonPath;
    QJsonObject jsonObj;
    loadJson(absDir, jsonObj);

    NodestGlobal::UIParameters* params = new NodestGlobal::UIParameters();

    // Parse inputFiles
    QJsonArray inputFilesArray = jsonObj["inputFiles"].toArray();
    for (const QJsonValue& inputFilesValue : inputFilesArray) {
        QJsonArray inputFilesInnerArray = inputFilesValue.toArray();
        std::vector<QString> innerVector;
        for (const QJsonValue& innerValue : inputFilesInnerArray) {
            innerVector.push_back(innerValue.toString());
            NodestGlobal::qmlFileNames.insert(innerValue.toString());
        }
        params->inputFiles.push_back(innerVector);
    }

    // Parse outputFiles
    QJsonArray outputFilesArray = jsonObj["outputFiles"].toArray();
    for (const QJsonValue& outputFilesValue : outputFilesArray) {
        QJsonArray outputFilesInnerArray = outputFilesValue.toArray();
        std::vector<QString> innerVector;
        for (const QJsonValue& innerValue : outputFilesInnerArray) {
            innerVector.push_back(innerValue.toString());
            NodestGlobal::qmlFileNames.insert(innerValue.toString());
        }
        params->outputFiles.push_back(innerVector);
    }

    // Parse inputNames
    QJsonArray inputNamesArray = jsonObj["inputNames"].toArray();
    for (const QJsonValue& inputNameValue : inputNamesArray) {
        params->inputNames.push_back(inputNameValue.toString());
    }

    // Parse outputNames
    QJsonArray outputNamesArray = jsonObj["outputNames"].toArray();
    for (const QJsonValue& outputNameValue : outputNamesArray) {
        params->outputNames.push_back(outputNameValue.toString());
    }

    // Parse nodeName
    params->nodeName = jsonObj["nodeName"].toString();
    params->nodeID = jsonObj["nodeID"].toString();
    params->baseFile = jsonObj["baseFile"].toString();
    params->baseTextFile = jsonObj["baseTextFile"].toString();
    NodestGlobal::qmlFileNames.insert(jsonObj["baseFile"].toString());
    NodestGlobal::qmlFileNames.insert(jsonObj["baseTextFile"].toString());

    return params;
}


bool Nodest::loadQmlByteArray(const QString &qmlPath, QByteArray &bytearray)
{
    QFile file(qmlPath);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to load QML file:" << qmlPath;
        return false;
    }

    bytearray = file.readAll();

    file.close();

    return true;
}

bool Nodest::loadJson(const QString &jsonPath, QJsonObject &jsonObj)
{
    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file:" << jsonPath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to create JSON document from file:" << jsonPath;
        return false;
    }

    jsonObj = jsonDoc.object();
    return true;
}
