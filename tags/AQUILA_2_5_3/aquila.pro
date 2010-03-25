include(config.pri)

TEMPLATE = subdirs
SUBDIRS = \
        src \
        examples

OTHER_FILES += CHANGELOG.txt \
               install.py
