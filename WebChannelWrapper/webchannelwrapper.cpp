#include "webchannelwrapper.h"

WebChannelWrapper::WebChannelWrapper(QObject *parent) : QObject(parent)
{
    QFileInfo jsFileInfo(QDir::currentPath() + "/qwebchannel.js");

              if (!jsFileInfo.exists())
                  QFile::copy(":/qtwebchannel/qwebchannel.js",jsFileInfo.absoluteFilePath());

        server = new QWebSocketServer("QWebChannel Server", QWebSocketServer::NonSecureMode);
        if(!server->listen(QHostAddress::LocalHost, 12345)) {
            qFatal("Failed to open web socket server.");
            return;
        }
        clientWrapper = new WebSocketClientWrapper(server);
        channel = new QWebChannel();
        QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
                         channel, &QWebChannel::connectTo);
        channel->registerObject("dialog",&dialog);
        //QUrl url = QUrl::fromLocalFile(BUILD_DIR "/index.html");
        //QDesktopServices::openUrl(url);

        datatosend = "joey says hello";
        dialog.sendData(datatosend);
        qDebug()<<"finished setting up"<<server<<channel;
        //QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(sendData()));
        //timer.start(500);
}

void WebChannelWrapper::sendData(QString Data){
    dialog.sendData(Data);
}
