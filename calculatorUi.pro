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
    tobase.cpp \
    test.cpp \
    right-paren.cpp \
    power.cpp \
    number.cpp \
    left-paren.cpp \
    helpdialog.cpp \
    negative_power.cpp

HEADERS  += mainwindow.h \
    division.hpp \
    multiplication.hpp \
    negative.hpp \
    operator_interface.hpp \
    shunting-yard.hpp \
    substraction.hpp \
    sum.hpp \
    right-paren.hpp \
    power.hpp \
    number.hpp \
    left-paren.hpp \
    decimal.h \
    helpdialog.h \
    negative_power.hpp

FORMS    += mainwindow.ui \
    helpdialog.ui

CONFIG += c++14
