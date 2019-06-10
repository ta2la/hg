TARGET       = hg_display
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11

INCLUDEPATH += ./ \
               ../hg_utility/include \
               ../hg_style \
#              ../hggesture_utility_ex/gesture_collect_style \
               ../../base/base/include \
               ../../base/base_ex/include \
               ../../base/geogebra \
               #../../base/infrastructure

INCLUDEPATH += ../../infrastructure/object_registry

#INCLUDEPATH += /usr/local/include/opencv

SOURCES     += ./*.cpp
HEADERS     += ./*.h

QT += widgets

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}
