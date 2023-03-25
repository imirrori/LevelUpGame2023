TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
       src/Game.cpp \
       src/Visualizer.cpp \
       App/main.cpp

HEADERS += \
       include/Game.hpp \
       include/Visualizer.hpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut
else:unix: LIBS += -L$$PWD/../../../glut/freeglut/freeglut/lib/x64/ -lfreeglut

INCLUDEPATH += $$PWD/../../../glut/freeglut/freeglut/include
DEPENDPATH += $$PWD/../../../glut/freeglut/freeglut/include

LIBS += -lopengl32
LIBS += -lglu32
