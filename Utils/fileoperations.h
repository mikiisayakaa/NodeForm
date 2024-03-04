#pragma once

#include "Global/globaluiparams.h"

#include <QJsonObject>

namespace NF{

NF::UIParameters* loadUIJson(const QString& jsonPath);

void loadGlobalUIJson(NF::GlobalUIParameters* param, const QString& jsonPath);

bool loadJson(const QString& jsonPath, QJsonObject& jsonObj);

bool loadQmlByteArray(const QString& qmlPath, QByteArray& bytearray);

}
