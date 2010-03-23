
EXAMPLES_ROOT_DIR = ..
include($${EXAMPLES_ROOT_DIR}/config.pri)

TARGET = wave_info
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
HEADERS += ../utils.h

