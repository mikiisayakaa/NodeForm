#pragma once

#include "Global/globaluiparams.h"

#include <QJsonObject>

namespace Nodest{

NodestGlobal::UIParameters* loadUIJson(const QString& jsonPath);

bool loadJson(const QString& jsonPath, QJsonObject& jsonObj);

bool loadQmlByteArray(const QString& qmlPath, QByteArray& bytearray);

}
