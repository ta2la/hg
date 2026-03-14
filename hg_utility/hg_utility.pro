TARGET       = hg_utility
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/include \
               $$PWD/../../base/base/include \
               $$PWD/../../base/geogebra \

SOURCES     += $$PWD/src/*.cpp
HEADERS     += $$PWD/include/*.h

QT += widgets
