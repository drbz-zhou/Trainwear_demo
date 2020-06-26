#include "imageprovider_plot.h"

ImageProvider_plot::ImageProvider_plot() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    m_plot = new QCustomPlot;
    m_plot->xAxis->setTicks(false);
    m_plot->xAxis->setTickLabels(false);
    m_plot->yAxis->rescale(true);
    m_plot->axisRect()->setupFullAxesBox();
    m_plot->legend->setVisible(true);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(20, 20, 20));
    m_plot->setBackground(plotGradient);

    // define the length of the graph in seconds
    m_graphLengthSeconds = 60;
    setDefaultColors();
    m_min=0;
    m_max=255;
}

QPixmap ImageProvider_plot::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    m_plot->replot();

    int width = 1000;
    int height = 1000;

    size->setHeight(height);
    size->setWidth(width);

    QPixmap plotImage(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    m_plot->yAxis->setRange(m_min, m_max);
    plotImage = m_plot->toPixmap(plotImage.width(),plotImage.height(),1.0);


    //m_plot->deleteLater();

    return plotImage;
}

void ImageProvider_plot::addDataToGraph(QString graphKey, double dataPoint){
   int graphId = 0;
   // find graphId for key,
   // if key does not exist add new graph
   if(!m_graphMap.contains(graphKey)){
      m_plot->addGraph();

      graphId = m_plot->graphCount()-1;

      QColor color =m_graphColorList.at(graphId);
      QPen pen(color);
      pen.setWidth(3);
      m_plot->graph(graphId)->setPen(pen);
      m_plot->graph(graphId)->setName(graphKey);
      m_graphMap.insert(graphKey,graphId);
      m_plotBuffers.resize(m_plot->graphCount());
      m_plotBuffers.last().setLength(TemporalBufferSize);
   }
   else{
       graphId = m_graphMap.value(graphKey);
   }

   // add point to graph
   double t = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
   m_plot->graph(graphId)->addData(t,dataPoint);
   m_plot->graph(graphId)->removeDataBefore(t-m_graphLengthSeconds);
   m_plotBuffers[graphId].circleAppend(dataPoint);
   //m_plot->graph(graphId)->rescaleValueAxis();
   m_plot->yAxis->setRange(m_min, m_max);
   m_plot->xAxis->setRange(t+0.25, 20, Qt::AlignRight);
   //m_plot->yAxis->setRange(m_plotBuffers[graphId].min(),m_plotBuffers[graphId].max());
}

void ImageProvider_plot::clearGraphs(){
    m_plot->clearGraphs();
    m_graphMap.clear();
}

void ImageProvider_plot::setDefaultColors(){
    m_graphColorList.clear();
    m_graphColorList.append(QColor(255, 0, 0));
    m_graphColorList.append(QColor(0, 255, 0));
    m_graphColorList.append(QColor(0, 0, 255));

    m_graphColorList.append(QColor(255, 0, 255));
    m_graphColorList.append(QColor(0, 255, 255));
    m_graphColorList.append(QColor(255, 128, 0));

    m_graphColorList.append(QColor(255, 255, 102));
    m_graphColorList.append(QColor(102, 153, 255));
    m_graphColorList.append(QColor(255, 255, 255));
}
void ImageProvider_plot::setYRange(double min, double max){
    m_min=min;
    m_max=max;
}
