QT += core gui widgets printsupport
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemographicSimulator
TEMPLATE = app

SOURCES += main.cpp \
           MainWindow.cpp \
           Country.cpp \
           SimulationModel.cpp \
           PDFReportGenerator.cpp

HEADERS += MainWindow.h \
           Country.h \
           SimulationModel.h \
           PDFReportGenerator.h
