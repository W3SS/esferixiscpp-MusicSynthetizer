QT += core
QT -= gui

CONFIG += c++11

TARGET = EsferixisCPP-MusicSynthetizer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    Common/Graph/Directed/meteoritocommondirectedgraphnodesconnector.h \
    Common/Dataflow/meteoritocommondataflowinput.h \
    Common/Dataflow/meteoritocommondataflowoutput.h

QMAKE_CXXFLAGS += -O2 -std=c++1z -Wall -Werror=delete-non-virtual-dtor -Werror=return-type
