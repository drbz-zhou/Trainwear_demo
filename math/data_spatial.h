#ifndef DATA_SPATIAL_H
#define DATA_SPATIAL_H

#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QTime>

class data_spatial
{
public:
    data_spatial(int numRows, int numCols);
    data_spatial();
    void setDim(int rows, int cols);
    void setValue(int row, int col, double value);
    void setValue(int index, double value);
    void setValueVector(QVector<double> valueVector);
    double value(int row, int col);
    double value(int index);
    int numRows();
    int numCols();
    int numel();

    double min();
    double max();
    data_spatial copy();
    void setValueAll(double value);

    // operator overloading
    friend QDataStream & operator<< (QDataStream& stream, const data_spatial& data);
    friend QDataStream & operator>> (QDataStream& stream, data_spatial& data);

    // time stamp
    void setCurrentTime();
    int getTimeVector();

    QVector<double> getDataLinear();
private:
    int m_rows;
    int m_cols;
    QVector<double> m_dataLinear;
    QTime timestamp;
};

#endif // DATA_SPATIAL_H
