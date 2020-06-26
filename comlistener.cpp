#include "comlistener.h"

COMListener::COMListener(QObject *parent) : QObject(parent)
{
    m_packetHead=-1;
    m_packetTail=-1;
    m_packetSize=104*2 + 8;
    m_newData=false;
    m_port = "COM3";
    m_header = "ff000000";
    m_headerSize = m_header.length();
    m_connected = false;
    m_started = false;
    m_cmd_lodged = false;
    m_0dataCounter=0;
}
void COMListener::setPort(QString portname){
    m_port = portname;
}
void COMListener::setPacketSize(int packetSize){
    m_packetSize = packetSize;
}

void COMListener::startlistener(){

}

void COMListener::run(){
    if(!m_connected){
        //start port only after moving listener to its own thread
        m_0dataCounter = 0;
        receivedall=0;
        serial.close();
        serial.clear();
        serial.setPortName(m_port);
        serial.setBaudRate(115200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.setReadBufferSize(1352);
        serial.open(QIODevice::ReadWrite);
        while(!serial.isOpen()){
            qDebug()<<"Error opening device"<<serial.error();
            serial.close();
            QThread::sleep(1);
            serial.open(QIODevice::ReadWrite);
        }
        QString filename  = "c:/data/shirt/"+m_fileName+".txt";

        pFileWorker.setFileName(filename.remove(" ") );
        while(!pFileWorker.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)){
            qDebug()<<"cannot open file: "<<pFileWorker.fileName()<<pFileWorker.isOpen();
            qDebug()<<pFileWorker.errorString()<<pFileWorker.exists();
        }
        qDebug()<<"COMListener: port opened!";
        m_connected = true;
    }else{

        if(serial.isOpen() && m_started){
            // if needs to send command
            if(m_cmd_lodged){
                //m_cmd_data = QByteArray::fromHex("02");
                if(!m_cmd_sent){
                    QByteArray cmd_send;
                    cmd_send.append("\x00");
                    cmd_send.append(QByteArray::fromHex(m_cmd_type));
                    cmd_send.append(QByteArray::fromHex(m_cmd_data));
                    cmd_send.append("\xff");
                    //cmd_send.append("00").append(m_cmd_type).append(m_cmd_data).append("ff");
                    qDebug()<<"sending cmd"<<cmd_send;
                    qDebug()<<serial.write(cmd_send);
                    m_cmd_sent = true;
                }else{
                    if(!m_cmd_verified){
                        m_cmd_back.append(serial.readAll().toHex());
                        QByteArray cmd_toprove = m_cmd_back.mid(2,(m_cmd_type.size()+m_cmd_data.size()));
                        qDebug()<<"cmd received: "<<cmd_toprove;
                        qDebug()<<(m_cmd_type+m_cmd_data);
                        if(cmd_toprove == (m_cmd_type+m_cmd_data) ){
                            qDebug()<<"return command match!";
                            m_cmd_verified=true;
                            m_cmd_lodged = false;
                            m_cmd_back.clear();
                        }
                    }
                }

            }

            // if no command is lodged
            else{

                m_mutex.lock();
                QByteArray newData = serial.readAll().toHex();
                //qDebug()<<QThread::currentThread()<<"starting com run"<<newData.size();
                if(!serial.isOpen()){
                    disconnect();
                }
                data += newData;
                receivedall+=data.size();
                //qDebug()<<QThread::currentThreadId()<<receivedall;


                qDebug()<<QThread::currentThread()<<"starting com run"<<data.size();
                m_packetHead = data.indexOf(m_header);
                if(m_packetHead != -1){
                    m_packetTail = data.indexOf(m_header, m_packetHead+m_packetSize);
                    if(m_packetTail != -1){

                        m_packetData = data.mid(m_packetHead+m_headerSize, m_packetSize-m_headerSize);
                        pFileWorker.write(t.currentTime().toString("hh:mm:ss:zzz").toUtf8().data());
                        pFileWorker.write(",");
                        pFileWorker.write(m_packetData);
                        pFileWorker.write("\n");

                        m_newData = true;

                        data.remove(0,m_packetTail);

                        qDebug()<<"Data size:"<<data.size();
                        m_packetTail = -1;
                    }
                    m_packetHead = -1;
                }

                // cleanse data buffer if overflows
                if(data.size()>4*m_packetSize){
                    qDebug()<<QThread::currentThreadId()<<"  Clear data overflow";
                    data.clear();
                    m_packetHead = -1;
                    m_packetTail = -1;
                }

                m_mutex.unlock();
            }
        }
    }
}

QByteArray COMListener::get_Packet(){
    QByteArray dataout;
    m_mutex.lock();
    dataout = m_packetData;
    m_newData = false;
    //m_packetData.clear();
    m_mutex.unlock();
    return dataout;
}
bool COMListener::ifNew(){
    return m_newData;
}
void COMListener::close(){
    serial.close();
}
bool COMListener::ifConnected(){
    return m_connected;
}
void COMListener::manualStart(){
    m_started = true;
}
void COMListener::disconnect(){
    m_connected = false;
}
void COMListener::setFileName(QString FileName){
    m_fileName.clear();
    m_fileName.append(FileName);
    QString timestamp = QDateTime::currentDateTime().toString("yyMMdd_hhmmss");
    m_fileName.append(timestamp);
}
void COMListener::send_cmd(QByteArray cmd_type, QByteArray cmd_data){
    m_mutex.lock();
    m_cmd_lodged = true;
    m_cmd_sent = false;
    m_cmd_verified = false;
    m_cmd_type = cmd_type;
    m_cmd_data = cmd_data;
    m_cmd_back.clear();
    m_mutex.unlock();
}
bool COMListener::ifCMDverified(){
    return m_cmd_verified;
}
