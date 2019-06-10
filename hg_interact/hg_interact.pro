TARGET       = hg_interact
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11

INCLUDEPATH += ./
INCLUDEPATH += ../hg_utility/include
INCLUDEPATH += ../hg_style
INCLUDEPATH += ../hg_display
INCLUDEPATH += ../../base/base/include
INCLUDEPATH += ../../base/base_ex/include
INCLUDEPATH += ../../base/geogebra
#INCLUDEPATH += ../../base/infrastructure
INCLUDEPATH += ../../infrastructure/object_registry
INCLUDEPATH += ../../infrastructure/command_registry
INCLUDEPATH += ../../infrastructure/command_registry_ex

SOURCES     += ./*.cpp
HEADERS     += ./*.h

QT += widgets

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

