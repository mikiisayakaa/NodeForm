#pragma once

#include <QString>
#include <QImage>

namespace NF{

static int idGenerator = 0;

QString convertImageToSourceString(const QImage& image);

QImage convertSourceStringToImage(const QString& str);

}
