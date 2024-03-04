#include "typeconversion.h"

#include <QBuffer>

namespace NF{

QString convertImageToSourceString(QImage &image)
{
    if (image.width() == 0){
        return "";
    }

    QImage scaledImg = image.scaled(212, 120, Qt::KeepAspectRatio);

    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    scaledImg.save(&buffer, "JPEG");

    QString imageBytes("data:image/jpg;base64,");
    imageBytes.append(QString::fromLatin1(bArray.toBase64().data()));

    return imageBytes;
}



}
