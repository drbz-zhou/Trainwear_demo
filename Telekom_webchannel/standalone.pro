QT += gui webchannel widgets websockets

CONFIG += warn_on


HEADERS += \
    WebChannelWrapper/websocketclientwrapper.h \
    WebChannelWrapper/websockettransport.h \
    WebChannelWrapper/webchanneldataobj.h \
    WebChannelWrapper/webchannelwrapper.h \
    mainobj.h

SOURCES += \
    main.cpp \
    WebChannelWrapper/websocketclientwrapper.cpp \
    WebChannelWrapper/websockettransport.cpp \
    WebChannelWrapper/webchanneldataobj.cpp \
    WebChannelWrapper/webchannelwrapper.cpp \
    mainobj.cpp

FORMS += \
    dialog.ui

DEFINES += "BUILD_DIR=\"\\\""$$OUT_PWD"\\\"\""

exampleassets.files += \
    index.html

