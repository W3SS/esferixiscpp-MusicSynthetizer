QT += core
QT -= gui

CONFIG += c++11

TARGET = EsferixisCPP-MusicSynthetizer
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += .

TEMPLATE = app

SOURCES += main.cpp \
    Common/Dataflow/esferixiscommondataflowconnection.cpp \
    Common/Dataflow/esferixiscommondataflowconnectionsmanager.cpp \
    Common/Dataflow/esferixiscommondataflowinterfaceelement.cpp \
    Common/Concurrency/esferixiscommonconcurrencypreventer.cpp

HEADERS += \
    Common/Dataflow/esferixiscommondataflowconcreteconnection.h \
    Common/Dataflow/esferixiscommondataflowconnection.h \
    Common/Dataflow/esferixiscommondataflowinput.h \
    Common/Dataflow/esferixiscommondataflowoutput.h \
    Common/Dataflow/esferixiscommondataflowconnectionsmanager.h \
    Common/Concurrency/esferixiscommonconcurrencypreventer.h \
    Common/Dataflow/esferixiscommondataflowinterfaceelement.h \
    Common/DataStructures/array.h

QMAKE_CXXFLAGS += -O2 -std=c++1z -Wall -Werror=delete-non-virtual-dtor -Werror=return-type
