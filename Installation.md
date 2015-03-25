# Building the library #

You need to have **Qt** installed as the library uses `qmake` as the build system. Boost C++ libraries are another required dependency.

First, get the code from Subversion repository.
```
svn checkout http://aquila.googlecode.com/svn/trunk/ aquila
cd aquila
```

**NOTE**: Two files must be modified by hand in order to correctly configure Boost paths. First, edit `config.pri` file located in the project root directory and modify the line
```
INCLUDEPATH += F:\boost_1_41_0
```
to your proper Boost installation root. Then, modify the `examples/config.pri` file and change all references to F:\boost\_1\_41\_0 to point to your Boost path. _Fortunately, with the coming Aquila 3 release there will be no need to hack around like that._

When done with editing, run the following commands:
```
qmake aquila.pro
make
```
(On Windows, replace `make` with `migw32-make`.)

# Installation #

I know, this is the painful part :( Either manually copy header files found in src/ subdirectory and binaries from lib/ subdirectory, or, if you have **Python** installed, use the `install.py` script. Running it may require administrative privileges.

The files `cfg_nt.py` (for Windows) and `cfg_posix.py` (for Linux) can be modified to tell the script where to install the binaries, headers and documentation.