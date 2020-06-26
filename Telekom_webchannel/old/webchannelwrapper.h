#ifndef WEBCHANNELWRAPPER_H
#define WEBCHANNELWRAPPER_H

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
#include <QObject>

class WebChannelWrapper : public QObject
{
    Q_OBJECT
public slots:
    void sendData(QString data);
public:
    explicit WebChannelWrapper(QObject *parent=0);
    QWebSocketServer* server;
    WebSocketClientWrapper* clientWrapper;
    QWebChannel* channel;
    WebChannelDataObj dialog;
    QTimer timer;
};

#endif // WEBCHANNELWRAPPER_H
