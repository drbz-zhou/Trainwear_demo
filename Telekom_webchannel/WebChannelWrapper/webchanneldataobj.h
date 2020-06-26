#ifndef WEBCHANNELDATAOBJ_H
#define WEBCHANNELDATAOBJ_H

#include <QObject>
#include <QDebug>

class WebChannelDataObj : public QObject
{
    Q_OBJECT
public:
    explicit WebChannelDataObj(QObject *parent = 0);
    void displayMessage(const QString &message);
    QString getReceivedData();
signals:
    /*!
        This signal is emitted from the C++ side and the text displayed on the HTML client side.
    */
    void sendText(const QString &text);

public slots:
    /*!
        This slot is invoked from the HTML client side and the text displayed on the server side.
    */
    void receiveText(const QString &text);
    void sendData(QString &datapacket);

private:
    QString receivedData;
};

#endif // WEBCHANNELDATAOBJ_H
