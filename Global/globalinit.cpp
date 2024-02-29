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

void NodestGlobal::fillNodeUImap(const QString &path)
{
    QDir directory(path);

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillNodeUImap(fileInfo.filePath());
        }
        else if (fileInfo.isFile() && fileInfo.suffix().toLower() == "json") {
            UIParameters* params = Nodest::loadUIJson(fileInfo.filePath());
            uiMap[params->nodeID] = params;
        }
    }
}

void NodestGlobal::fillGlobalUI(const QString &path)
{
    QDir directory(path);

    NodestGlobal::globalUi = new NodestGlobal::GlobalUIParameters;

    QFileInfoList fileInfoList = directory.entryInfoList();

    foreach (const QFileInfo& fileInfo, fileInfoList) {
        if (fileInfo.isDir() && fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            fillNodeUImap(fileInfo.filePath());
        }
        else if (fileInfo.isFile() && fileInfo.fileName() == "globalUI.json") {
            //load global ui
            Nodest::loadGlobalUIJson(NodestGlobal::globalUi, fileInfo.filePath());
        }
    }
}

void NodestGlobal::fillQmlData(const QString& path, QQmlEngine* engine, QHash<QString, QQmlComponent*>& mp)
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
            if (NodestGlobal::qmlFileNames.find(filename) == NodestGlobal::qmlFileNames.end()){
                continue;
            }

            QByteArray bytearray;
            Nodest::loadQmlByteArray(fileInfo.filePath(), bytearray);
            QQmlComponent* component = new QQmlComponent(engine);
            component->setData(bytearray, QUrl("file:///" + path));
            mp[fileInfo.fileName()] = component;

            NodestGlobal::qmlFileNames.remove(filename);
        }
    }


}

void NodestGlobal::fillQmlGSData(const QString& path, QQmlEngine* engine, QHash<QString, setGetInfo>& mp)
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
            Nodest::loadQmlByteArray(fileInfo.filePath(), bytearray);
            QQmlComponent* component = new QQmlComponent(engine);
            component->setData(bytearray, QUrl("file:///" + path));

            QString typeName;
            QObject* tempObj = component->create();
            typeName = tempObj->property("typeName").toString();
            delete tempObj;

            mp[filename] = setGetInfo{component, typeName};

            NodestGlobal::qmlFileNames.remove(filename);
        }
    }
}

void NodestGlobal::setQmlDefault(const QString &path, QString &defaultFile)
{
    //load default json
    QJsonObject jsonObj;
    Nodest::loadJson(path + "default.json", jsonObj);
    defaultFile = jsonObj["default"].toArray()[0].toString();
    qmlFileNames.insert(defaultFile);
}

void NodestGlobal::setQmlGSDefault(const QString &path, QSet<QString> &defaultFiles)
{
    QJsonObject jsonObj;
    Nodest::loadJson(path + "default.json", jsonObj);

    QJsonArray jsonArray = jsonObj["default"].toArray();
    for (const auto& filename: jsonArray){
        defaultFiles.insert(filename.toString());
        qmlFileNames.insert(filename.toString());
    }
}


void NodestGlobal::fillDummy(QQmlEngine* engine)
{
    QString path = qmlPath + "GlobalWidgets/" + dummyFile;

    QByteArray bytearray;
    Nodest::loadQmlByteArray(path, bytearray);
    dummy = new QQmlComponent(engine);
    dummy->setData(bytearray, QUrl("file:///" + path));

    //put it in all map lists
    slotSetterMap[dummyFile] = setGetInfo{dummy, ""};
    slotGetterMap[dummyFile] = setGetInfo{dummy, ""};
    slotHandleMap[dummyFile] = dummy;
    textLabelMap[dummyFile] = dummy;

}

//void NodestGlobal::fillBackground(QQmlEngine *engine)
//{
//    QString path = uiPath + backgroundFile;

//    QByteArray bytearray;
//    Nodest::loadQmlByteArray(path, bytearray);
//    bgd = new QQmlComponent(engine);
//    bgd->setData(bytearray, QUrl("file:///" + path));
//}

//void NodestGlobal::fillConnectionLine(QQmlEngine *engine)
//{
//    QString path = uiPath + lineFile;

//    QByteArray bytearray;
//    Nodest::loadQmlByteArray(path, bytearray);
//    connectionLine = new QQmlComponent(engine);
//    connectionLine->setData(bytearray, QUrl("file:///" + path));
//}

//called at init stage of the program
void NodestGlobal::prepareUIWidgets(QQmlEngine *engine)
{
    for (auto& jsonPath : NodestGlobal::nodeJsonPaths){
        fillNodeUImap(jsonPath);
    }

    for (auto& globaljsonPath : NodestGlobal::globalJsonPaths){
        fillGlobalUI(globaljsonPath);
    }

    for (auto& bgdPath : NodestGlobal::qmlBackgroundPath){
        setQmlDefault(bgdPath, backgroundDefault);
        fillQmlData(bgdPath, engine, backgroundMap);
    }

    for (auto& curvePath : NodestGlobal::qmlCurvePaths){
        setQmlDefault(curvePath, curveDefault);
        fillQmlData(curvePath, engine, curveMap);
    }

    fillDummy(engine);

    //always set default first, we need to add the default file to qmlFileNames
    for (auto& handlePath : NodestGlobal::qmlHandlesPaths){
        setQmlDefault(handlePath, slotHandleDefault);
        fillQmlData(handlePath, engine, slotHandleMap);
    }

    for (auto& textlabelPath : NodestGlobal::qmlTextLabelsPaths){
        setQmlDefault(textlabelPath, textLabelDefault);
        fillQmlData(textlabelPath, engine, textLabelMap);
    }

    for (auto& nodeBasePath : NodestGlobal::qmlNodeBasePaths){
        setQmlDefault(nodeBasePath, nodeBaseDefault);
        fillQmlData(nodeBasePath, engine, nodeBaseMap);
    }

    for (auto& setterPath : NodestGlobal::qmlSettersPaths){
        setQmlGSDefault(setterPath, slotSetterDefault);
        fillQmlGSData(setterPath, engine, slotSetterMap);
    }

    for (auto& getterPath : NodestGlobal::qmlGettersPaths){
        setQmlGSDefault(getterPath, slotGetterDefault);
        fillQmlGSData(getterPath, engine, slotGetterMap);
    }
}


void NodestGlobal::globalInit(QApplication *app)
{
    //enable multisampling
    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine* engine = new QQmlApplicationEngine;
    NodestGlobal::engine = engine;


    const QUrl url("file:///" + NodestGlobal::qmlMainPath);
    QObject::connect(NodestGlobal::engine, &QQmlApplicationEngine::objectCreated,
                    app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    NodestGlobal::engine->load(url);

    NodestGlobal::prepareUIWidgets(NodestGlobal::engine);

    QObject* root = NodestGlobal::engine->rootObjects()[0]->children().at(0);
    NodestGlobal::globalRootObject = qobject_cast<QQuickItem*>(root);

    Nodest::AbstractNodeGraph* graph = new Nodest::BasicNodeGraph();
    Nodest::AbstractGraphObject* graphObj = new Nodest::BasicGraphObject(graph, nullptr);

    NodestGlobal::globalGraphObject = graphObj;
    qDebug() << "----------------------";
    QObject::connect(app, &QApplication::aboutToQuit, &NodestGlobal::cleanupGraph);
}





