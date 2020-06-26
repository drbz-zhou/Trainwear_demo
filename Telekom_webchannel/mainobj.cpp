#include "mainobj.h"

mainobj::mainobj(QObject *parent) : QObject(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(send()));
    m_timer.start(1000);
}

void mainobj::send(){
    QString datatosend;
    for(int i=0; i<128;i++){
        datatosend.append(QString::number(x++)).append(",");
    }
    qDebug()<<"sending."<<datatosend;
    m_WebChannel.sendData(datatosend);
}
