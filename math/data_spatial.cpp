#include "data_spatial.h"

data_spatial::data_spatial(int numRows, int numCols)
{
    m_dataLinear.resize(numRows * numCols);
    m_rows = numRows;
    m_cols = numCols;
}

data_spatial::data_spatial()
{
    m_dataLinear.resize(0);
    m_rows = 0;
    m_cols = 0;
}

void data_spatial::setDim(int rows, int cols){
    m_rows = rows;
    m_cols = cols;
}

void data_spatial::setValue(int row, int col, double value){
    if(row < 0 || row > m_rows-1 ||
       col < 0 || col > m_cols-1 )
    {
        qDebug() << "DataFrame::setValue: Error: index out of range, row: " << row << " col:" << col;
        return;
    }
    m_dataLinear[row * m_cols + col] = value;
}

void data_spatial::setValue(int index, double value){
    if(index < 0 || index >= m_rows*m_cols)
    {
        qDebug() << "DataFrame::setValue: Error: index out of range, index: " << index;
        return;
    }
    m_dataLinear[index] = value;
}


void data_spatial::setValueVector(QVector<double> valueVector){
    m_dataLinear = valueVector;
}

double data_spatial::value(int row, int col){
    if(row < 0 || row > m_rows-1 ||
       col < 0 || col > m_cols-1 )
    {
        qDebug() << "DataFrame::value: Error: index out of range";
        return 0;
    }
    return m_dataLinear[row * m_cols + col];
}
double data_spatial::value(int index){
if(index < 0 || index >= m_rows*m_cols)
    {
        qDebug() << "DataFrame::value: Error: index out of range";
        return 0;
    }
    return m_dataLinear[index];
}

int data_spatial::numRows(){
    return m_rows;
}
int data_spatial::numCols(){
    return m_cols;
}
int data_spatial::numel(){
    return m_dataLinear.length();
}

double data_spatial::min(){

    if(m_dataLinear.length() == 0){
        qDebug() << "DataFrame::min: frame has no elements";
        return 0;
    }

    double min = m_dataLinear[0];
    for(int i = 1; i < m_dataLinear.length(); i++){
        if(m_dataLinear[i] < min){
            min = m_dataLinear[i];
        }
    }
    return min;
}
double data_spatial::max(){
    if(m_dataLinear.length() == 0){
        qDebug() << "DataFrame::max: frame has no elements";
        return 0;
    }

    double max = m_dataLinear[0];

    for(int i = 1; i < m_dataLinear.length(); i++){

        if(m_dataLinear[i] > max){
            max = m_dataLinear[i];
        }
    }

    return max;
}

data_spatial data_spatial::copy(){
    data_spatial newFrame(m_rows,m_cols);
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            newFrame.setValue(i,j,this->value(i,j));
        }
    }
    return newFrame;
}
void data_spatial::setValueAll(double value){
     for(int i = 0; i < m_cols*m_rows; i++){
        this->m_dataLinear[i] = value;
     }
}

void data_spatial::setCurrentTime(){
    timestamp = QTime::currentTime();}

int data_spatial::getTimeVector(){
    int timeInt=0;
    timeInt += timestamp.toString("zzz").toInt();
    timeInt += timestamp.toString("ss").toInt()*1000;
    timeInt += timestamp.toString("mm").toInt()*60000;
    timeInt += timestamp.toString("hh").toInt()*3600000;
    return timeInt;
}


QDataStream & operator<< (QDataStream& stream, const data_spatial& data)
{
  // write frame to stream
  stream << data.m_rows;
  stream << data.m_cols;
  stream << data.m_dataLinear;
  stream << data.timestamp;
  return stream;
}

QDataStream & operator>> (QDataStream& stream, data_spatial& data){
    // read frame from stream
    stream >> data.m_rows;
    stream >> data.m_cols;
    stream >> data.m_dataLinear;
    stream >> data.timestamp;
    return stream;
}

QVector<double> data_spatial::getDataLinear(){
    return m_dataLinear;
}
