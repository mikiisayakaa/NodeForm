#pragma once

#include <QImage>

namespace Nodest{

void imageDisplay(const QImage& srcImage, QImage& rstImage);

void loadImage(const QString& url, QImage& image);

void inverseImage(const QImage& srcImage, QImage& rstImage);

void brightness(const QImage& srcImage, const int& val, QImage& rstImage);

void grayScale(const QImage& srcImage, QImage& rstImage);

}
