#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T16:16:56
#
#-------------------------------------------------

QT       += core gui serialport opengl quick printsupport webchannel widgets websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuitTry
TEMPLATE = app

INCLUDEPATH += C:/opencv/opencv/build/include
#INCLUDEPATH += /usr/local/Cellar/opencv3/3.1.0_3/include

SOURCES += main.cpp\
        mainwindow.cpp \
    comlistener.cpp \
    qcustomplot/qcustomplot.cpp \
    qmlagent.cpp \
    mathagent.cpp \
    sensorunit.cpp \
    imageprovider_matrix.cpp \
    imageprovider_plot.cpp \
    math/lpfilter.cpp \
    math/data_spatial.cpp \
    math/data_temporal.cpp \
    math/data_tempo_spatial.cpp \
    math/cv_spatialmethods.cpp \
    sensorspecs.cpp \
    WebChannelWrapper/webchanneldataobj.cpp \
    WebChannelWrapper/webchannelwrapper.cpp \
    WebChannelWrapper/websocketclientwrapper.cpp \
    WebChannelWrapper/websockettransport.cpp

HEADERS  += mainwindow.h \
    comlistener.h \
    qcustomplot/qcustomplot.h \
    qmlagent.h \
    mathagent.h \
    sensorunit.h \
    sensorspecs.h \
    imageprovider_matrix.h \
    imageprovider_plot.h \
    math/lpfilter.h \
    math/data_spatial.h \
    math/data_temporal.h \
    math/data_tempo_spatial.h \
    math/cv_spatialmethods.h \
    WebChannelWrapper/webchanneldataobj.h \
    WebChannelWrapper/webchannelwrapper.h \
    WebChannelWrapper/websocketclientwrapper.h \
    WebChannelWrapper/websockettransport.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    SuitView.qml

RESOURCES += \
    resources.qrc

LIBS += -LC:\\opencv\\opencv_bin\\bin \
    libopencv_core248d \
    libopencv_highgui248d \
    libopencv_imgproc248d \
    libopencv_features2d248d \
    libopencv_calib3d248d \
    libopencv_ml248d \
    libopencv_contrib248d \
#LIBS += -L/usr/local/Cellar/opencv3/3.1.0_3/lib \
#    -lopencv_core \
#    -lopencv_highgui \
#    -lopencv_imgproc \
#    -lopencv_features2d \
    #-lopencv_alib3d \
#    -lopencv_ml \
    #-lopencv_contrib \
