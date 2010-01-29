EXAMPLES_ROOT_DIR = ..
include($${EXAMPLES_ROOT_DIR}/config.pri)

TARGET = benchmark
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    Benchmark.cpp

# extra libraries
HEADERS += Benchmark.h
