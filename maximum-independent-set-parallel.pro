TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graphboost.cpp \
    graphmatrix.cpp

LIBS += -lboost_system \
        -lboost_thread \

HEADERS += \
    graphboost.h \
    graphmatrix.h \
    graphmatrix.h \
    graphboost.h

