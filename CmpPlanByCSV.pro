#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T02:29:31
#
#-------------------------------------------------

QT       += core gui
DESTDIR = ./bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CmpPlanByCSV
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    plan.cpp

HEADERS  += dialog.h \
    plan.h

FORMS    += dialog.ui

OTHER_FILES += \
    bin/set.ini
