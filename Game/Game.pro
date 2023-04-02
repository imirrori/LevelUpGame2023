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
       include/Global_settings.h \
       include/Visualizer.hpp


INCLUDEPATH += $$PWD/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3

INCLUDEPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include
DEPENDPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll

INCLUDEPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include
DEPENDPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include

LIBS += -lopengl32
LIBS += -lglfw3
