#ifndef DATA_TEMPORAL_H
#define DATA_TEMPORAL_H

#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QTime>

class data_temporal
{
public:
    data_temporal();
    data_temporal(int lengthLim);

    //input

    void setValue(int index, double value);
    void insert(int index, double value);
    void append(double value);
    void circleAppend(double value);
    void prepend(double value);
    void setLength(int lengthLim);

    //output
    double at(int index);
    QVector<double> mid(int index, int length);
    data_temporal copy();
    int size();

    //numeritic
    double min();
    double max();

    void trim();
private:
    QVector<double> m_dataLinear;
    int m_lengthLim;
};

#endif // DATA_TEMPORAL_H
