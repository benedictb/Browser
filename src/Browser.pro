#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T15:12:36
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Browser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    histstack.cpp \
    bookmarkdialog.cpp

HEADERS  += mainwindow.h \
    histstack.h \
    bookmarkdialog.h

FORMS    += mainwindow.ui \
    bookmarkdialog.ui
