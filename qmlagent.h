#ifndef QMLAGENT_H
#define QMLAGENT_H

#include <QObject>

#include <QQmlApplicationEngine>
#include "imageprovider_matrix.h"
#include "imageprovider_plot.h"
#include "sensorspecs.h"
#include "math/data_spatial.h"
#include <QVector>

class QMLAgent : public QObject
{
    Q_OBJECT
public:
    explicit QMLAgent(QObject *parent = 0);
    void drawFrame_1(data_spatial A1_data2D, data_spatial A2_data2D, data_spatial A3_data2D);
    void drawFrame_2(data_spatial A4_data2D, data_spatial A5_data2D);
    void addDataToGraph(QString graphKey, double dataPoint);
    void setYRange(double min, double max);
    void drawFrame(int matrix_number, data_spatial data2D);
signals:

public slots:

private:

    QQmlApplicationEngine m_qmlEngine;
    ImageProvider_matrix matrixprovider_1;
    ImageProvider_matrix matrixprovider_2;
    ImageProvider_matrix matrixprovider_3;
    ImageProvider_matrix matrixprovider_4;
    ImageProvider_matrix matrixprovider_5;
    ImageProvider_matrix matrixprovider_6;
    ImageProvider_matrix matrixprovider_7;
    ImageProvider_matrix matrixprovider_8;
    ImageProvider_matrix matrixprovider_9;
    ImageProvider_matrix matrixprovider_10;
    ImageProvider_matrix matrixprovider_11;
    ImageProvider_matrix matrixprovider_12;
    ImageProvider_plot plotprovider_1;
    QObject *m_qmlRootObject;
    QObject *m_qmlMatrixObject_1;
    QObject *m_qmlMatrixObject_2;
    QObject *m_qmlMatrixObject_3;
    QObject *m_qmlMatrixObject_4;
    QObject *m_qmlMatrixObject_5;
    QObject *m_qmlMatrixObject_6;
    QObject *m_qmlMatrixObject_7;
    QObject *m_qmlMatrixObject_8;
    QObject *m_qmlMatrixObject_9;
    QObject *m_qmlMatrixObject_10;
    QObject *m_qmlMatrixObject_11;
    QObject *m_qmlMatrixObject_12;
    QObject *m_qmlPlotObject_1;

    QVector<QObject*> m_qmlMatrixObjectList;
    QVector<ImageProvider_matrix*> m_MatrixProviderList;
};

#endif // QMLAGENT_H
