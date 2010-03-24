
QT -= core gui

AQUILA_ROOT_DIR = ..
include($${AQUILA_ROOT_DIR}/config.pri)


TEMPLATE = subdirs
SUBDIRS = \
            benchmark \
            dtw_distance \
            simple_extraction \
            wave_info
