#pragma once

#include <QQuickImageProvider>

class PixmapProvider: public QQuickImageProvider
{
public:
    PixmapProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap) {}

    void setImage(QImage* image) {m_image = image;}

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QImage* m_image;
};
