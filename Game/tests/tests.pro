TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        SettingsTests.cpp \
        ../src/Settings.cpp \
        main.cpp

INCLUDEPATH += $$PWD/../include

linux: LIBS += -L$$PWD/../../../../googletest/build-googletest-Desktop-Debug/ -lgoogletest
linux: INCLUDEPATH += $$PWD/../../../../googletest/googletest/include
linux: DEPENDPATH += $$PWD/../../../../googletest/googletest/include
