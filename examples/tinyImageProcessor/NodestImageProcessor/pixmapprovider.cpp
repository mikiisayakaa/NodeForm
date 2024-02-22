#include "pixmapprovider.h"

QPixmap PixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = m_image->width();
    int height = m_image->height();

    if (size){
        *size = QSize(width, height);
    }
    QPixmap pixmap = QPixmap::fromImage(*m_image);

    pixmap.scaled(requestedSize, Qt::KeepAspectRatio);
    return pixmap;
}
