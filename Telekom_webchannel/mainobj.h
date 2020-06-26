#ifndef MAINOBJ_H
#define MAINOBJ_H

#include <QObject>
#include "WebChannelWrapper/webchannelwrapper.h"
#include <QTimer>

class mainobj : public QObject
{
    Q_OBJECT
public:
    explicit mainobj(QObject *parent = 0);
    WebChannelWrapper m_WebChannel;
    QTimer m_timer;
    int x=1;

signals:

public slots:
    void send();
};

#endif // MAINOBJ_H
