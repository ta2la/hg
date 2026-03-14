TARGET       = hg_display
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/ \
               $$PWD/../hg_text \
               $$PWD/../hg_utility/include \
               $$PWD/../hg_papper \
               $$PWD/../hg_style \
               $$PWD/../../base/base/include \
               $$PWD/../../base/geogebra

INCLUDEPATH += $$PWD/../../infrastructure/object_registry

#INCLUDEPATH += /usr/local/include/opencv

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

QT += widgets

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

DISTFILES += \
    hg_display.qmodel


