# -*- coding: utf-8 -*-
import os
import shutil

# SETTINGS FOR MICROSOFT WINDOWS SYSTEMS

# you can change the directory below
INSTALL_BASE_DIR = r"F:\aquila"
INSTALL_LIB_DIR = os.path.join(INSTALL_BASE_DIR, "lib")
INSTALL_SRC_DIR = os.path.join(INSTALL_BASE_DIR, r"include\aquila")
INSTALL_DOC_DIR = os.path.join(INSTALL_BASE_DIR, "doc")

def prepare():
    if os.path.exists(INSTALL_BASE_DIR):
        print "Looks like it's gonna be an upgrade..."
        shutil.rmtree(INSTALL_BASE_DIR)
    os.mkdir(INSTALL_BASE_DIR)
    print "Created install directory"
