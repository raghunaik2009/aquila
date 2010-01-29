
QT -= core gui

win32 {
    INCLUDEPATH += F:\boost_1_41_0
}
# AQUILA
win32 {
    INCLUDEPATH += F:\aquila\include
    DEFINES += AQUILA_DLL
    LIBS += -LF:\aquila\lib
    CONFIG(debug, debug|release):LIBS += -laquilad2
    CONFIG(release, debug|release):LIBS += -laquila2
}
unix {
    INCLUDEPATH += /usr/include/aquila
    LIBS += -L/usr/lib/aquila
    LIBS += -laquila
}
