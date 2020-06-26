#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include <QObject>
#include <QVector>
#include <QTime>
#include <QDebug>
#include "math/lpfilter.h"
#include "math/data_spatial.h"
#include "math/data_temporal.h"

class SensorUnit : public QObject
{
    Q_OBJECT
public:
    explicit SensorUnit(QObject *parent = 0);
    void setDims(int xdim, int ydim);
    void updateValsVector(QVector<double> vals);
    void setValAt(double val, int x, int y);
    QVector<double> getValsVector();
    void setFirstInd(int first);
    void temp_setLength(int length);
    void temp_append(double value);
    double filter_apply(double newSample);

    int m_firstind;
    int m_lastind;
    int m_numel;

    data_spatial copyData2D();
    data_temporal m_wave;
signals:

public slots:
private:
    //QVector<double> m_vals;
    QVector<int> m_x;
    QVector<int> m_y;
    QTime m_timestamp;

    int m_xdim;
    int m_ydim;

    data_spatial m_data2D;


    lpfilter m_filter;
};

#endif // SENSORUNIT_H
