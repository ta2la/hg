TARGET       = hg_style
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/ \
               $$PWD/../../hg/hg_utility/include \
               $$PWD/../../evo/storage_base/include \
               $$PWD/../../base/base/include \
               $$PWD/../../base/geogebra

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}
