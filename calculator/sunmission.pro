QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Имя исполняемого файла
TARGET = calculator
TEMPLATE = app

# Список исходников и заголовков
SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    calculator.h \
    mainwindow.h