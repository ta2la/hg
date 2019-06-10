TARGET       = hg_style
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11

INCLUDEPATH += ./ \
               ../../hg/hg_utility/include \
               ../../base/base/include \
               ../../base/base_ex/include \
               ../../base/geogebra

SOURCES     += ./*.cpp
HEADERS     += ./*.h

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

