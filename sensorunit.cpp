#include "sensorunit.h"

SensorUnit::SensorUnit(QObject *parent) : QObject(parent)
{
    m_xdim = 0;
    m_ydim = 0;
    m_numel = 0;
    m_firstind = 0;
    m_lastind = 0;
}

void SensorUnit::setDims(int xdim, int ydim){
    m_xdim = xdim;
    m_ydim = ydim;
    m_numel = xdim*ydim;
    m_x.clear();
    m_y.clear();
    for(int x=0; x<m_xdim; x++){
        for(int y=0; y<m_ydim; y++){
            m_x.append(x);
            m_y.append(y);
        }
    }
    m_data2D.setDim(xdim, ydim);
    //qDebug()<<m_numel<<m_x<<m_y;
}
void SensorUnit::setFirstInd(int first){
    m_firstind = first;
    m_lastind = m_firstind + m_numel;
}

void SensorUnit::updateValsVector(QVector<double> vals){
    m_data2D.setValueVector(vals);
}
void SensorUnit::setValAt(double val, int x, int y){
    if(x < m_xdim && y < m_ydim){
        m_data2D.setValue(x+y*m_ydim, val);
    }
}
QVector<double> SensorUnit::getValsVector(){
    return m_data2D.getDataLinear();
}
data_spatial SensorUnit::copyData2D(){
    return m_data2D.copy();
}
void SensorUnit::temp_setLength(int length){
    m_wave.setLength(length);
}
void SensorUnit::temp_append(double value){
    m_wave.append(value);
}
double SensorUnit::filter_apply(double newSample){
    return m_filter.applyfilter(newSample);
}
