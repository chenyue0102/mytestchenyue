TEMPLATE = app
CONFIG += console c++11
SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../include

opt = $$find(QMAKESPEC,"msvc2015_64")
isEmpty(opt){
LIBS += -L$$PWD/../../lib/win32
}
!isEmpty(opt){
LIBS += -L$$PWD/../../lib/win64
}

