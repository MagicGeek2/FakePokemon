QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
    tcpserver.cpp \
    sql.cpp \
    socketthread.cpp \
    server_m.cpp \
    socket_m.cpp

HEADERS  += \
    tcpserver.h \
    sql.h \
    socketthread.h \
    server_m.h \
    socket_m.h

FORMS    += \
    tcpserver.ui
