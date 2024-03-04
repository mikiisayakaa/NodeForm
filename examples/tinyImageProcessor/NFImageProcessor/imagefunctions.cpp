#include "imagefunctions.h"

#include <QDebug>

void NF::imageDisplay(const QImage &srcImage, QImage &rstImage)
{
    //shallow copy of QImage
    rstImage = srcImage;
}


void NF::loadImage(const QString &url, QImage &image)
{
    if(url == ""){
        return;
    }
    //remove "file:///" from url's head
    QString filePath = url.mid(8);
    bool ok = image.load(filePath);
}

void NF::inverseImage(const QImage &srcImage, QImage &rstImage)
{
    rstImage = srcImage;

    for (int i = 0; i < rstImage.height(); i++){
        QRgb* line = (QRgb*)rstImage.scanLine(i);
        for (int j = 0; j < rstImage.width(); j++){
            line[j] = qRgb(255 - qRed(line[j]), 255 - qGreen(line[j]), 255 - qBlue(line[j]));
        }
    }
}

void NF::brightness(const QImage &srcImage, const int &val, QImage &rstImage)
{
    rstImage = srcImage;
    for (int i = 0; i < rstImage.height(); i++){
        QRgb* line = (QRgb*)rstImage.scanLine(i);
        for (int j = 0; j < rstImage.width(); j++){
            int red = qRed(line[j]) + val;
            red = red > 255 ? 255 : (red < 0 ? 0 : red);
            int green = qGreen(line[j]) + val;
            green = green > 255 ? 255 : (green < 0 ? 0 : green);
            int blue = qBlue(line[j]) + val;
            blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
            line[j] = qRgb(red, green, blue);
        }
    }
}

void NF::grayScale(const QImage &srcImage, QImage &rstImage)
{
    rstImage = srcImage;

    for (int i = 0; i < rstImage.height(); i++){
        QRgb* line = (QRgb*)rstImage.scanLine(i);
        for (int j = 0; j < rstImage.width(); j++){
            int avg = (qRed(line[j]) * 299 + qGreen(line[j]) * 587 + qBlue(line[j]) * 112 + 500)/ 1000;
            line[j] = qRgb(avg, avg, avg);
        }
    }
}
