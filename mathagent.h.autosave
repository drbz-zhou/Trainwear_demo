#ifndef MATHAGENT_H
#define MATHAGENT_H

#include <QObject>
#include <QVector>
#include <QDebug>

class mathagent : public QObject
{
    Q_OBJECT
public:
    explicit mathagent(QObject *parent = 0);
    QVector<double> parseBytePacket(QByteArray byteData);
    double mean(QVector<double> input);
    QString VecDouble2Str(QVector<double>  input);
};

#endif // MATHAGENT_H
