TARGET       = hg_papper
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/ \
               $$PWD/../hg_utility/include \
               $$PWD/../hg_display \
               $$PWD/../hg_style \
               $$PWD/../../base/base/include \
               $$PWD/../../base/geogebra \

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

QT += widgets

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}
