#include "imageprovider_matrix.h"


ImageProvider_matrix::ImageProvider_matrix() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{


    m_primaryColor = "purple";
    m_pixelWidth = 3;
    m_pixelHeight = 3;
    m_pixelSpacing = 1;
}

QPixmap ImageProvider_matrix::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QCustomPlot *plot = new QCustomPlot;
    QCPColorMap *colorMap = new QCPColorMap(plot->xAxis,plot->yAxis);
    plot->addPlottable(colorMap);
    plot->xAxis->setVisible( false );
    plot->yAxis->setVisible( false );

    int nx = m_data2D.numRows();
    int ny = m_data2D.numCols();

    colorMap->data()->setSize(nx,ny);
    colorMap->data()->setRange(QCPRange(0, nx), QCPRange(0, ny));

//    qDebug()<<m_data2D.numCols()<<m_data2D.numRows();
//    double max = frame.max();
//    double min = frame.min();
    //test

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){

            double value =  m_data2D.value(i+j*nx);
            //colorMap->data()->setCell(i,j,value);
            //colorMap->data()->setCell(nx-i-1, j, value); // mirror x
            colorMap->data()->setCell(i, ny-j-1, value); // mirror y
        }
    }

    //customColorGrad.clearColorStops();
    //customColorGrad.setColorStopAt(0,QColor("purple").darker(100));
    //customColorGrad.setColorStopAt(1,QColor("white"));

    QCPColorGradient customColorGrad;
    customColorGrad.loadPreset(QCPColorGradient::gpThermal);

    colorMap->setGradient(customColorGrad);
    colorMap->rescaleDataRange(true); // dynamic range

    //QCPRange range(0,0.02); // fixed range
    //colorMap->setDataRange(range);


    colorMap->setInterpolate( false);

    //colorMap->setDataRange( QCPRange(this->range_min, this->range_max));


    plot->axisRect()->setAutoMargins( QCP::msNone );
    plot->axisRect()->setMargins( QMargins(-1,-1,-1,-1) );
    plot->plotLayout()->setAutoMargins( QCP::msLeft );
    plot->plotLayout()->setMargins( QMargins(0,0,0,0));
    plot->xAxis->setRange(-0.5, nx + 0.5);
    plot->yAxis->setRange(-0.5, ny + 0.5);


    plot->replot();

    int width = 500;
    int height = 1000;
    QPixmap plotImage(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    plotImage = plot->toPixmap(plotImage.width(),plotImage.height(),1.0);

    plot->deleteLater();
    colorMap->deleteLater();

    return plotImage;

//    int width = m_pixelColumns * (m_pixelWidth + m_pixelSpacing) - m_pixelSpacing;
//    int height = m_pixelRows * (m_pixelHeight + m_pixelSpacing) - m_pixelSpacing;

//    if (size)
//        *size = QSize(width, height);


//    pixmap.fill(Qt::transparent);
//    QPainter painter;

//    double max = m_frame.max();
//    double min = m_frame.min();

//    if (max < 0.005){
//        max = 0.005;
//    }



//    painter.begin(&pixmap);
//    painter.beginNativePainting();

//    //qDebug() << m_pixelRows << " " << m_pixelColumns;
//    QElapsedTimer etimer;
//    etimer.start();

//    for(int i = 0; i < m_pixelRows; i++){
//        for(int j = 0; j < m_pixelColumns; j++){
//            int w = m_pixelWidth;
//            int h = m_pixelHeight;
//            int s = m_pixelSpacing;
//            int y = i*(w+s);
//            int x = j*(h+s);

//            double value = (m_frame.value(i,j)-min)/(max-min);

//            QColor primaryColor = m_primaryColor;

//            painter.fillRect(x, y, w, h, QBrush(primaryColor.lighter(100 + value*500)));
//        }
//    }
//    painter.endNativePainting();
//    qDebug() << "request " << etimer.elapsed();

//    painter.end();


}


void ImageProvider_matrix::updateFrame(data_spatial data2D){
    m_data2D=data2D.copy();
}
