#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
# DO NOT MODIFY, SETTINGS ARE LOCATED IN cfg_nt.py / cfg_posix.py
################################################################################

import os
import shutil

try:
    cfg = __import__('cfg_%s' % os.name)
except ImportError:
    print 'Sorry, your system is not supported yet!'
    import sys
    sys.exit(1)

for path in (cfg.INSTALL_LIB_DIR, cfg.INSTALL_DOC_DIR, cfg.INSTALL_SRC_DIR):
    if os.path.exists(path):
        print "Removing files from %s" % path
        shutil.rmtree(path)

cfg.prepare()

AQUILA_DIR = os.path.dirname(__file__)
AQUILA_LIB_DIR = os.path.join(AQUILA_DIR, "lib")
AQUILA_SRC_DIR = os.path.join(AQUILA_DIR, "src")
AQUILA_DOC_DIR = os.path.join(AQUILA_DIR, "doc")
ignore = shutil.ignore_patterns('.svn*', '*.cpp', '*.rc', '*.pro*', 'Makefile*',
                                'debug', 'release', 'obj', 'objd', 'object_script.*')
print "Copying libraries from %s to %s" % (AQUILA_LIB_DIR, cfg.INSTALL_LIB_DIR)
shutil.copytree(AQUILA_LIB_DIR, cfg.INSTALL_LIB_DIR, ignore=ignore)
print "Copying include files from %s to %s" % (AQUILA_SRC_DIR, cfg.INSTALL_SRC_DIR)
shutil.copytree(AQUILA_SRC_DIR, cfg.INSTALL_SRC_DIR, ignore=ignore)
print "Copying documentation from %s to %s" % (AQUILA_DOC_DIR, cfg.INSTALL_DOC_DIR)
shutil.copytree(AQUILA_DOC_DIR, cfg.INSTALL_DOC_DIR, ignore=ignore)
