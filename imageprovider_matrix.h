#ifndef IMAGEPROVIDER_MATRIX_H
#define IMAGEPROVIDER_MATRIX_H


#include <QPixmap>
#include <QQuickImageProvider>
#include <QPainter>
#include <QOpenGLPaintDevice>
#include <QDebug>
#include <QElapsedTimer>
#include <qcustomplot/qcustomplot.h>
#include "math/data_spatial.h"

class ImageProvider_matrix : public QQuickImageProvider
{

public:
    ImageProvider_matrix();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    void updateFrame(data_spatial data2D);
private:
    QColor m_primaryColor;
    int m_pixelWidth;
    int m_pixelHeight;
    int m_pixelSpacing;

    double m_noiseLevel;

    data_spatial m_data2D;
};

#endif // IMAGEPROVIDER_MATRIX_H
