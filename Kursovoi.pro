#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T22:31:23
#
#-------------------------------------------------

QT       += core gui sql printsupport xml script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Kursovoi
TEMPLATE = app
RC_ICONS=res\home.ico
#Z:/bin/
win32:CONFIG(release, debug|release) : LIBS += -Lbin/ -lNCReport2
else:win32:CONFIG(debug, debug|release): LIBS += -Lbin/ -lNCReportDebug2
INCLUDEPATH +=bin
INCLUDEPATH +=lib
INCLUDEPATH +=platforms
SOURCES += main.cpp\
        mainwindow.cpp \
    pictures_stroitel.cpp \
    database.cpp \
    query_result.cpp \
    my_function_for_ui.cpp \
    query_void.cpp \
    dir.cpp \
    plan_building_time.cpp \
    info_ui_function.cpp \
    building_ui_function.cpp \
    group_eqw_special.cpp \
    worker_ui.cpp \
    technics_ui.cpp \
    material_client_ui.cpp \
    printer.cpp

HEADERS  += mainwindow.h \
    database.h \
    pictures_stroitel.h \
    query_result.h \
    dir.h \
    plan_building_time.h \
    printer.h \
    struct_data.h

FORMS    += mainwindow.ui

RESOURCES += \
    resurs.qrc
