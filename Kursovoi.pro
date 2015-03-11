#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T22:31:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursovoi
TEMPLATE = app
RC_ICONS=res\home.ico


SOURCES += main.cpp\
        mainwindow.cpp \
    pictures_stroitel.cpp \
    poisk_material.cpp \
    database.cpp \
    worker.cpp \
    building.cpp \
    technics.cpp \
    material.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    poisk_material.h \
    database.h \
    worker.h \
    building.h \
    technics.h \
    material.h \
    client.h \
    pictures_stroitel.h

FORMS    += mainwindow.ui \
    poisk_material.ui



RESOURCES += \
    resurs.qrc
