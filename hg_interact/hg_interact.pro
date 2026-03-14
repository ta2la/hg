TARGET       = hg_interact
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

RESOURCES += $$PWD/resources/hg_interact.qrc

INCLUDEPATH += $$PWD/
INCLUDEPATH += $$PWD/../hg_utility/include
INCLUDEPATH += $$PWD/../hg_papper
INCLUDEPATH += $$PWD/../hg_style
INCLUDEPATH += $$PWD/../hg_display
INCLUDEPATH += $$PWD/../../base/base/include
INCLUDEPATH += $$PWD/../../base/geogebra
INCLUDEPATH += $$PWD/../../infrastructure/object_registry
INCLUDEPATH += $$PWD/../../infrastructure/command_registry
INCLUDEPATH += $$PWD/../../infrastructure/command_registry_ex

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

QT += widgets

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

QT += quick quickwidgets
