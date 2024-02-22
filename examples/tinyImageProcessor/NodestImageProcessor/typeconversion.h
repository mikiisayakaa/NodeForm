#pragma once

#include <QString>
#include <QImage>

namespace Nodest{

static int idGenerator = 0;

QString convertImageToSourceString(QImage& image);

}
