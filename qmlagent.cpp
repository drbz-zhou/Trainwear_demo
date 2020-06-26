#include "qmlagent.h"

QMLAgent::QMLAgent(QObject *parent) : QObject(parent)
{
    // load qml file into engine
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_1"), &matrixprovider_1);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_2"), &matrixprovider_2);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_3"), &matrixprovider_3);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_4"), &matrixprovider_4);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_5"), &matrixprovider_5);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_6"), &matrixprovider_6);

    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_7"), &matrixprovider_7);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_8"), &matrixprovider_8);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_9"), &matrixprovider_9);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_10"), &matrixprovider_10);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_11"), &matrixprovider_11);
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_12"), &matrixprovider_12);
    m_qmlEngine.addImageProvider(QLatin1String("plot_Provider_1"), &plotprovider_1);
    m_qmlEngine.load(QUrl(QStringLiteral("qrc:/SuitView.qml")));
    // access root object
    m_qmlRootObject = m_qmlEngine.rootObjects().value(0);
    // access canvas obejct
    m_qmlMatrixObject_1 = m_qmlRootObject->findChild<QObject *>("matrix_1",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_2 = m_qmlRootObject->findChild<QObject *>("matrix_2",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_3 = m_qmlRootObject->findChild<QObject *>("matrix_3",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_4 = m_qmlRootObject->findChild<QObject *>("matrix_4",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_5 = m_qmlRootObject->findChild<QObject *>("matrix_5",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_6 = m_qmlRootObject->findChild<QObject *>("matrix_6",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_7 = m_qmlRootObject->findChild<QObject *>("matrix_7",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_8 = m_qmlRootObject->findChild<QObject *>("matrix_8",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_9 = m_qmlRootObject->findChild<QObject *>("matrix_9",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_10 = m_qmlRootObject->findChild<QObject *>("matrix_10",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_11 = m_qmlRootObject->findChild<QObject *>("matrix_11",Qt::FindDirectChildrenOnly);
    m_qmlMatrixObject_12 = m_qmlRootObject->findChild<QObject *>("matrix_12",Qt::FindDirectChildrenOnly);
    m_qmlPlotObject_1 = m_qmlRootObject->findChild<QObject *>("plot_1",Qt::FindDirectChildrenOnly);

    m_qmlMatrixObjectList.append(m_qmlMatrixObject_1);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_2);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_3);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_4);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_5);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_6);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_7);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_8);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_9);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_10);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_11);
    m_qmlMatrixObjectList.append(m_qmlMatrixObject_12);

    m_MatrixProviderList.append(&matrixprovider_1);
    m_MatrixProviderList.append(&matrixprovider_2);
    m_MatrixProviderList.append(&matrixprovider_3);
    m_MatrixProviderList.append(&matrixprovider_4);
    m_MatrixProviderList.append(&matrixprovider_5);
    m_MatrixProviderList.append(&matrixprovider_6);
    m_MatrixProviderList.append(&matrixprovider_7);
    m_MatrixProviderList.append(&matrixprovider_8);
    m_MatrixProviderList.append(&matrixprovider_9);
    m_MatrixProviderList.append(&matrixprovider_10);
    m_MatrixProviderList.append(&matrixprovider_11);
    m_MatrixProviderList.append(&matrixprovider_12);

    qDebug()<<"qml::"<<m_MatrixProviderList.size()<<m_qmlMatrixObjectList.size();
}

void QMLAgent::drawFrame_1(data_spatial A1_data2D, data_spatial A2_data2D, data_spatial A3_data2D){
    matrixprovider_1.updateFrame(A1_data2D);
    matrixprovider_2.updateFrame(A2_data2D);
    matrixprovider_3.updateFrame(A3_data2D);

    QMetaObject::invokeMethod(m_qmlMatrixObject_1, "updateGrid");
    QMetaObject::invokeMethod(m_qmlMatrixObject_2, "updateGrid");
    QMetaObject::invokeMethod(m_qmlMatrixObject_3, "updateGrid");
}

void QMLAgent::drawFrame_2(data_spatial A4_data2D, data_spatial A5_data2D){
    matrixprovider_4.updateFrame(A4_data2D);
    matrixprovider_5.updateFrame(A5_data2D);

    QMetaObject::invokeMethod(m_qmlMatrixObject_4, "updateGrid");
    QMetaObject::invokeMethod(m_qmlMatrixObject_5, "updateGrid");
}

void QMLAgent::addDataToGraph(QString graphKey, double dataPoint){
    plotprovider_1.addDataToGraph(graphKey, dataPoint);

    QMetaObject::invokeMethod(m_qmlPlotObject_1, "updatePlot");
}
void QMLAgent::setYRange(double min, double max){
    plotprovider_1.setYRange(min,max);
}
void QMLAgent::drawFrame(int matrix_number, data_spatial data2D){
    m_MatrixProviderList.at(matrix_number)->updateFrame(data2D);
    QMetaObject::invokeMethod(m_qmlMatrixObjectList.at(matrix_number), "updateGrid");
}
