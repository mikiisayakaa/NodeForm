#include "globalinit.h"
#include "globalpaths.h"
#include "Utils/fileoperations.h"
#include "globalitems.h"
#include "Core/basicnodegraph.h"
#include "Interface/basicgraphobject.h"
#include "globalcleanup.h"

#include <QDir>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQuickItem>

void NF::fillNodeUImap(const QString &path)
{
    QDir directory(path);

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillNodeUImap(fileInfo.filePath());
        }
        else if (fileInfo.isFile() && fileInfo.suffix().toLower() == "json") {
            UIParameters* params = NF::loadUIJson(fileInfo.filePath());
            uiMap[params->nodeID] = params;
        }
    }
}

void NF::fillGlobalUI(const QString &path)
{
    QDir directory(path);

    NF::globalUI = new NF::GlobalUIParameters;

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillNodeUImap(fileInfo.filePath());
        }
        else if (fileInfo.isFile() && fileInfo.fileName() == "globalUI.json") {
            //load global ui
            NF::loadGlobalUIJson(NF::globalUI, fileInfo.filePath());
        }
    }
}

void NF::fillQmlData(const QString& path, QQmlEngine* engine, QHash<QString, QQmlComponent*>& mp)
{
    QDir directory(path);


    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillQmlData(fileInfo.absoluteFilePath(), engine, mp);
        }
        else if (fileInfo.isFile() && fileInfo.suffix().toLower() == "qml") {
            QString filename = fileInfo.fileName();
            //check if the qml is used by the user, also ensure at least one handle is available
            if (NF::qmlFileNames.find(filename) == NF::qmlFileNames.end()){
                continue;
            }

            QByteArray bytearray;
            NF::loadQmlByteArray(fileInfo.filePath(), bytearray);
            QQmlComponent* component = new QQmlComponent(engine);
            component->setData(bytearray, QUrl("file:///" + path));
            mp[fileInfo.fileName()] = component;

            NF::qmlFileNames.remove(filename);
        }
    }


}

void NF::fillQmlGSData(const QString& path, QQmlEngine* engine, QHash<QString, setGetInfo>& mp)
{
    QDir directory(path);

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillQmlGSData(fileInfo.absoluteFilePath(), engine, mp);
        }
        else if (fileInfo.isFile() && fileInfo.suffix().toLower() == "qml") {
            QString filename = fileInfo.fileName();

            //since setters have different types, we have to load all qmls
            //need better implementation

            QByteArray bytearray;
            NF::loadQmlByteArray(fileInfo.filePath(), bytearray);
            QQmlComponent* component = new QQmlComponent(engine);
            component->setData(bytearray, QUrl("file:///" + path));

            QString typeName;
            QObject* tempObj = component->create();
            typeName = tempObj->property("typeName").toString();
            delete tempObj;

            mp[filename] = setGetInfo{component, typeName};

            NF::qmlFileNames.remove(filename);
        }
    }
}

void NF::fillQmlDataBridgeData(const QString &path, QQmlEngine *engine, QHash<QString, NF::DataBridgeInfo> &mp)
{
    QDir directory(path);

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillQmlDataBridgeData(fileInfo.absoluteFilePath(), engine, mp);
        }
        else if (fileInfo.isFile() && fileInfo.suffix().toLower() == "qml") {
            QString filename = fileInfo.fileName();


            QByteArray bytearray;
            NF::loadQmlByteArray(fileInfo.filePath(), bytearray);
            QQmlComponent* component = new QQmlComponent(engine);
            component->setData(bytearray, QUrl("file:///" + path));

            QString cppType, qmlType;
            QObject* tempObj = component->create();
            cppType = tempObj->property("cppType").toString();
            qmlType = tempObj->property("qmlType").toString();
            delete tempObj;

            DataBridgeInfo dbinfo{component, cppType, qmlType};
            mp[filename] = dbinfo;

            NF::qmlFileNames.remove(filename);
        }
    }
}

void NF::setQmlDefault(const QString &path, QString &defaultFile)
{
    //load default json
    QJsonObject jsonObj;
    NF::loadJson(path + "default.json", jsonObj);
    defaultFile = jsonObj["default"].toArray()[0].toString();
    qmlFileNames.insert(defaultFile);
}

void NF::setQmlGSDefault(const QString &path, QSet<QString> &defaultFiles)
{
    QJsonObject jsonObj;
    NF::loadJson(path + "default.json", jsonObj);

    QJsonArray jsonArray = jsonObj["default"].toArray();
    for (const auto& filename: jsonArray){
        defaultFiles.insert(filename.toString());
        qmlFileNames.insert(filename.toString());
    }
}

void NF::setQmlDataBridgeDefault(const QString &path, QSet<QString> &defaultFiles)
{
    QJsonObject jsonObj;
    NF::loadJson(path + "default.json", jsonObj);

    QJsonArray jsonArray = jsonObj["default"].toArray();
    for (const auto& filename: jsonArray){
        defaultFiles.insert(filename.toString());
        qmlFileNames.insert(filename.toString());
    }
}





void NF::fillDummy(QQmlEngine* engine)
{
    QString path = qmlPath + "GlobalWidgets/" + dummyFile;

    QByteArray bytearray;
    NF::loadQmlByteArray(path, bytearray);
    dummy = new QQmlComponent(engine);
    dummy->setData(bytearray, QUrl("file:///" + path));

    //put it in all map lists
    slotSetterMap[dummyFile] = setGetInfo{dummy, ""};
    slotGetterMap[dummyFile] = setGetInfo{dummy, ""};
    slotHandleMap[dummyFile] = dummy;
    textLabelMap[dummyFile] = dummy;

}

//called at init stage of the program
void NF::prepareUIWidgets(QQmlEngine *engine)
{
    for (auto& jsonPath : NF::nodeJsonPaths){
        fillNodeUImap(jsonPath);
    }

    for (auto& globaljsonPath : NF::globalJsonPaths){
        fillGlobalUI(globaljsonPath);
    }

    for (auto& bgdPath : NF::qmlBackgroundPath){
        setQmlDefault(bgdPath, backgroundDefault);
        fillQmlData(bgdPath, engine, backgroundMap);
    }

    for (auto& curvePath : NF::qmlCurvePaths){
        setQmlDefault(curvePath, curveDefault);
        fillQmlData(curvePath, engine, curveMap);
    }

    fillDummy(engine);

    //always set default first, we need to add the default file to qmlFileNames
    for (auto& handlePath : NF::qmlHandlesPaths){
        setQmlDefault(handlePath, slotHandleDefault);
        fillQmlData(handlePath, engine, slotHandleMap);
    }

    for (auto& textlabelPath : NF::qmlTextLabelsPaths){
        setQmlDefault(textlabelPath, textLabelDefault);
        fillQmlData(textlabelPath, engine, textLabelMap);
    }

    for (auto& nodeBasePath : NF::qmlNodeBasePaths){
        setQmlDefault(nodeBasePath, nodeBaseDefault);
        fillQmlData(nodeBasePath, engine, nodeBaseMap);
    }

    for (auto& setterPath : NF::qmlSettersPaths){
        setQmlGSDefault(setterPath, slotSetterDefault);
        fillQmlGSData(setterPath, engine, slotSetterMap);
    }

    for (auto& getterPath : NF::qmlGettersPaths){
        setQmlGSDefault(getterPath, slotGetterDefault);
        fillQmlGSData(getterPath, engine, slotGetterMap);
    }

    for (auto& dataBridgePath : NF::qmlDataBridgePaths){
        setQmlDataBridgeDefault(dataBridgePath, dataBridgeDefault);
        fillQmlDataBridgeData(dataBridgePath, engine, dataBridgeMap);
    }
}


void NF::globalInit(QApplication *app)
{
    //enable multisampling
    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine* engine = new QQmlApplicationEngine;
    NF::engine = engine;


    const QUrl url("file:///" + NF::qmlMainPath);
    QObject::connect(NF::engine, &QQmlApplicationEngine::objectCreated,
                    app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    NF::engine->load(url);

    NF::prepareUIWidgets(NF::engine);

    QObject* root = NF::engine->rootObjects()[0]->children().at(0);
    NF::globalRootObject = qobject_cast<QQuickItem*>(root);

    NF::AbstractNodeGraph* graph = new NF::BasicNodeGraph();
    NF::AbstractGraphObject* graphObj = new NF::BasicGraphObject(graph, nullptr);

    NF::globalGraphObject = graphObj;
    qDebug() << "----------------------";
    QObject::connect(app, &QApplication::aboutToQuit, &NF::cleanupGraph);
}

