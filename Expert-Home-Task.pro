include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

HEADERS += \
    helperclass.h \
    types.h

SOURCES += \
    main.cpp \
    helperclass.cpp \
    test\test_helperclass.cpp
