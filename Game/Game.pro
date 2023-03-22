TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Game.cpp \
        Visualizer.cpp \
        main.cpp

HEADERS += \
    Game.h \
    Visualizer.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut
else:unix: LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut

INCLUDEPATH += $$PWD/../../../glut/freeglut/freeglut/include
DEPENDPATH += $$PWD/../../../glut/freeglut/freeglut/include

LIBS += -lopengl32
LIBS += -lglu32
