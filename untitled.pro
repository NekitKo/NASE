QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    consoleclient.cpp \
    main.cpp \
    mainwindow.cpp \
    task_solution.cpp

HEADERS += \
    auth.h \
    consoleclient.h \
    mainwindow.h \
    task_solution.h

FORMS += \
    auth.ui \
    mainwindow.ui \
    task_solution.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
