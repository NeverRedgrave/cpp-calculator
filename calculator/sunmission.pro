QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = calculator
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    calculator.cpp

HEADERS += \
    calculator.h \
    mainwindow.h
