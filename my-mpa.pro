TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BigInt_IO.cpp \
    BIgInt_Arithm.cpp \
    BigInt_Cmp.cpp \
    BigInt_Mod.cpp \
    BigInt_Other.cpp

HEADERS += \
    BigInt.h

QMAKE_CXXFLAGS += -std=c++11
