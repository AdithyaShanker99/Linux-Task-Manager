QT       += core gui printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    cpuGraphs.cpp\
    DirectoryStruct.cpp \
    memoryGraphs.cpp \
    Processes.cpp \
    sysInfo.cpp \
    qcustomplot.cpp \
    network_monitor.cpp \
    system_info.cpp \
    test.cpp

HEADERS += \
    mainwindow.h \
    cpuGraphs.h \
    DirectoryStruct.h \
    memoryGraphs.h \
    Processes.h \
    sysInfo.h \
    qcustomplot.h \
    network_monitor.h \
    system_info.h \
    test.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
