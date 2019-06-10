TARGET       = hg_utility
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11

INCLUDEPATH += ./include \
               ../../base/base/include \
               ../../base/geogebra \

SOURCES     += ./src/*.cpp
HEADERS     += ./include/*.h

QT += widgets
