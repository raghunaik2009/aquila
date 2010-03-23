
QT -= core gui

AQUILA_ROOT_DIR = ..

include($${AQUILA_ROOT_DIR}/config.pri)

SUFFIX_STR =
CONFIG(debug, debug|release) {
    SUFFIX_STR = $${DEBUG_SUFFIX}
}
else {
    SUFFIX_STR = $${RELEASE_SUFFIX}
}

TARGET = aquila$${SUFFIX_STR}
TEMPLATE = lib

OBJECTS_DIR       = obj$${SUFFIX_STR}
DESTDIR           = $${AQUILA_ROOT_DIR}/lib

contains(CONFIG, AquilaDll) {
    CONFIG += dll
}
else {
    CONFIG += staticlib
}
win32:AquilaDll {
    DEFINES    += QT_DLL AQUILA_DLL AQUILA_MAKEDLL
}


HEADERS +=      WaveFile.h \
    Tools.h \
    Exceptions.h \
    Frame.h \
    Transform.h \
    Window.h \
    MelFilter.h \
    MelFiltersBank.h \
    feature/Extractor.h \
    feature/FeatureWriter.h \
    feature/TextFeatureWriter.h \
    feature/FeatureReader.h \
    feature/EnergyExtractor.h \
    feature/MfccExtractor.h \
    feature/HfccExtractor.h \
    feature/PowerExtractor.h \
    feature/ExtractorFactory.h \
    ProcessingIndicator.h \
    ConsoleProcessingIndicator.h \
    dtw/DtwPoint.h \
    dtw/functions.h \
    dtw/Dtw.h \
    global.h
SOURCES +=       WaveFile.cpp \
    Tools.cpp \
    Frame.cpp \
    Transform.cpp \
    Window.cpp \
    MelFilter.cpp \
    MelFiltersBank.cpp \
    feature/Extractor.cpp \
    feature/FeatureWriter.cpp \
    feature/TextFeatureWriter.cpp \
    feature/FeatureReader.cpp \
    feature/EnergyExtractor.cpp \
    feature/MfccExtractor.cpp \
    feature/HfccExtractor.cpp \
    feature/PowerExtractor.cpp \
    feature/ExtractorFactory.cpp \
    ConsoleProcessingIndicator.cpp \
    dtw/DtwPoint.cpp \
    dtw/functions.cpp \
    dtw/Dtw.cpp
