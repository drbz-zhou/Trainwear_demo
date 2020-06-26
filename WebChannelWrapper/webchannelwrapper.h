#ifndef WEBCHANNELWRAPPER_H
#define WEBCHANNELWRAPPER_H

#include <QObject>
#include "websocketclientwrapper.h"
#include "webchanneldataobj.h"
#include "websockettransport.h"
#include <QtWebSockets/QWebSocketServer>
#include "qwebchannel.h"
#include <QUrl>
#include <QDir>
#include <QDesktopServices>
#include <QFileInfo>
#include <QTimer>

class WebChannelWrapper : public QObject
{
    Q_OBJECT
public:
    explicit WebChannelWrapper(QObject *parent = 0);
    QWebSocketServer* server;
    WebSocketClientWrapper* clientWrapper;
    QWebChannel* channel;
    WebChannelDataObj dialog;
    //QTimer timer;
    QString datatosend;

signals:

public slots:
    void sendData(QString Data);
};

#endif // WEBCHANNELWRAPPER_H
