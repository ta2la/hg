TARGET       = hg_text
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

win32 {
DEFINES += WINDOWS
}

INCLUDEPATH += $$PWD/ \
               $$PWD/../../hg/hg_utility/include \
               $$PWD/../../hg/hg_papper \
               $$PWD/../../hg/hg_style \
               $$PWD/../../hg/hg_display \
               $$PWD/../../hg/hg_interact \
               $$PWD/../../base/base/include \
               $$PWD/../../infrastructure/command_registry \
               $$PWD/../../infrastructure/command_registry_ex \
               $$PWD/../../infrastructure/object_registry \
               $$PWD/../../cvz/cvz-engine \
               $$PWD/../../base/geogebra \
               $$PWD/../../evo/storage_base/include \
               $$PWD/../../evo/storage \
               $$PWD/../../evo/cad \
               $$PWD/../../evo/cad_infrastructure \
               $$PWD/../../cad_professional/cad_professional_lib \
               $$PWD/../../evo/cad_attrs \
               $$PWD/../../cad/cad_settings

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

QT += widgets
