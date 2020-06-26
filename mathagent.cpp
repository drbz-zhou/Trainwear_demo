#include "mathagent.h"

mathagent::mathagent(QObject *parent) : QObject(parent)
{

}

QVector<double> mathagent::parseBytePacket(QByteArray byteData){
    int ptr;
    int ptr_step=2;
    int ptr_offset=0;
    QVector<double> currentPacket;
    for(ptr=0; ptr<byteData.size();ptr=ptr+ptr_step){
        QByteArray byteField = byteData.mid(ptr+ptr_offset, ptr_step-ptr_offset);
        bool ok;
        double dataValue = byteField.toLong(&ok, 16); //hex to int

        /// correct for twos complement
        currentPacket.append(dataValue);
    }
    //qDebug()<<byteData;
    return currentPacket;
}

double mathagent::mean(QVector<double> input){
    double meanval = 0;
    for(int i=0; i<input.size(); i++){
        meanval += input.at(i);
    }
    meanval /= input.size();
    return meanval;
}

QString mathagent::VecDouble2Str(QVector<double>  input){
    QString output;
    qDebug()<<input.size()<<input;
    for(int i=0; i<input.size(); i++){
        output.append(QString::number(input.at(i))).append(",");
    }
    return output;
}
