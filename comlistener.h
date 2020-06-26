#ifndef COMLISTENER_H
#define COMLISTENER_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QTimer>
#include <QFile>
#include <QTime>
#include <QVector>

class COMListener : public QObject
{
    Q_OBJECT
public:
    explicit COMListener(QObject *parent = 0);
    void startlistener();
    QByteArray get_Packet();
    void setPort(QString portname);
    void setPacketSize(int packetsize);
    bool ifNew();
    void close();
    bool ifConnected();
    void manualStart();
    void disconnect();
    void setFileName(QString FileName);
    void send_cmd(QByteArray cmd_type, QByteArray cmd_data);
    bool ifCMDverified();
    QString m_port;
    QVector<double> currentPacket;
signals:

public slots:
    void run();

private:

    QSerialPort serial;
    QByteArray data;
    long int receivedall;

    int m_packetHead;
    int m_packetTail;
    int m_packetSize;
    int m_headerSize;
    QByteArray m_header;

    QByteArray m_packetData;
    bool m_newData;
    bool m_connected;
    bool m_started;

    QMutex m_mutex;

    int m_0dataCounter;

    QFile pFileWorker;
    QTime t;
    QString m_fileName;

    bool m_cmd_lodged;
    bool m_cmd_sent;
    bool m_cmd_verified;
    QByteArray m_cmd_type;
    QByteArray m_cmd_data;
    QByteArray m_cmd_back;
};

#endif // COMLISTENER_H
