#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import shutil

# change the directory below
INSTALL_DIR = r"F:\aquila"
AQUILA_DIR = os.path.dirname(__file__)

AQUILA_LIB_DIR = os.path.join(AQUILA_DIR, "lib")
INSTALL_LIB_DIR = os.path.join(INSTALL_DIR, "lib")
AQUILA_SRC_DIR = os.path.join(AQUILA_DIR, "src")
INSTALL_SRC_DIR = os.path.join(INSTALL_DIR, r"include\aquila")
AQUILA_DOC_DIR = os.path.join(AQUILA_DIR, "doc")
INSTALL_DOC_DIR = os.path.join(INSTALL_DIR, "doc")

if os.name == 'posix':
    INSTALL_LIB_DIR = "/usr/lib/aquila"
    INSTALL_SRC_DIR = "/usr/include/aquila"
    INSTALL_DOC_DIR = "/usr/share/doc/aquila"
    
    for path in (INSTALL_LIB_DIR, INSTALL_DOC_DIR, INSTALL_SRC_DIR):
        if os.path.exists(path):
            print "Removing files from %s" % path
            shutil.rmtree(path)
        
else:
    print "Installing from %s to %s" % (AQUILA_DIR, INSTALL_DIR)

    if os.path.exists(INSTALL_DIR):
        print "Looks like it's gonna be an upgrade..."
        shutil.rmtree(INSTALL_DIR)
        
    os.mkdir(INSTALL_DIR)
    print "Created install directory"
	
ignore = shutil.ignore_patterns('.svn*', '*.cpp', '*.rc', '*.pro*', 'Makefile*', 'debug', 'release',
								'obj', 'objd', 'object_script.*')

print "Copying libraries from %s to %s" % (AQUILA_LIB_DIR, INSTALL_LIB_DIR)
shutil.copytree(AQUILA_LIB_DIR, INSTALL_LIB_DIR, ignore=ignore)

print "Copying include files from %s to %s" % (AQUILA_SRC_DIR, INSTALL_SRC_DIR)
shutil.copytree(AQUILA_SRC_DIR, INSTALL_SRC_DIR, ignore=ignore)

print "Copying documentation from %s to %s" % (AQUILA_DOC_DIR, INSTALL_DOC_DIR)
shutil.copytree(AQUILA_DOC_DIR, INSTALL_DOC_DIR, ignore=ignore)
