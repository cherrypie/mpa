TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    LongNumber_Other.cpp \
    LongNumber_Modular.cpp \
    LongNumber_Logic.cpp \
    LongNumber_Base.cpp \
    LongNumber_Arithmetic.cpp

HEADERS += \
    LongNumber.h

QMAKE_CXXFLAGS += -std=c++11
