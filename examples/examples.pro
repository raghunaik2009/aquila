
QT -= core gui

AQUILA_ROOT_DIR = ..
include($${AQUILA_ROOT_DIR}/config.pri)


TEMPLATE = subdirs
SUBDIRS = \
            benchmark \
            simple_extraction \
            wave_info
