
VERSION = 2.5.1

CONFIG += AquilaDll

DEBUG_SUFFIX = 
RELEASE_SUFFIX = 
win32 {
    # CONFIG           += debug_and_release
    # CONFIG           += build_all
    DEBUG_SUFFIX = d
}
else {
}

# extra libraries
INCLUDEPATH += F:\boost_1_41_0
