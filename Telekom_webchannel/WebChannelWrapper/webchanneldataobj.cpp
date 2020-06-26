#include "webchanneldataobj.h"

WebChannelDataObj::WebChannelDataObj(QObject *parent) : QObject(parent)
{

}
void WebChannelDataObj::displayMessage(const QString &message)
{
    qDebug()<<message;
}
void WebChannelDataObj::receiveText(const QString &text)
{
    receivedData = text;
    qDebug()<<"received: "<<receivedData;
}

void WebChannelDataObj::sendData(QString &datapacket){
    emit sendText(datapacket);
    //qDebug()<<"sending data";
}
QString WebChannelDataObj::getReceivedData(){
    return receivedData;
}
