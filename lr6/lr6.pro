QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    config.cpp \
    cube.cpp \
    drawer.cpp \
    figure.cpp \
    figurewrapper.cpp \
    main.cpp \
    mainwindow.cpp \
    shaderprogramwrapper.cpp \
    stuff.cpp \
    viewmatrixwrapper.cpp

HEADERS += \
    arrow.h \
    config.h \
    cube.h \
    drawer.h \
    figure.h \
    figurewrapper.h \
    mainwindow.h \
    shaderprogramwrapper.h \
    stuff.h \
    viewmatrixwrapper.h

FORMS += \
    mainwindow.ui

LIBS += -lopengl32 -lglu32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    shaders.qrc
