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
    database.cpp \
    worker.cpp \
    building.cpp \
    technics.cpp \
    material.cpp \
    client.cpp \
    query_result.cpp \
    my_function_for_ui.cpp \
    query_void.cpp \
    dir.cpp \
    plan_building_time.cpp \
    info_ui_function.cpp

HEADERS  += mainwindow.h \
    database.h \
    worker.h \
    building.h \
    technics.h \
    material.h \
    client.h \
    pictures_stroitel.h \
    query_result.h \
    dir.h \
    plan_building_time.h

FORMS    += mainwindow.ui



RESOURCES += \
    resurs.qrc
