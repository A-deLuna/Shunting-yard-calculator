#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T22:28:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calculatorUi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    division.cpp \
    multiplication.cpp \
    negative.cpp \
    regex_tokenizer.cpp \
    shunting-yard.cpp \
    substraction.cpp \
    sum.cpp \
    tobase.cpp

HEADERS  += mainwindow.h \
    division.hpp \
    multiplication.hpp \
    negative.hpp \
    operator_interface.hpp \
    shunting-yard.hpp \
    substraction.hpp \
    sum.hpp

FORMS    += mainwindow.ui

CONFIG += c++14
