TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
       src/Game.cpp \
       src/Player.cpp \
       src/Visualizer.cpp \
       App/main.cpp

HEADERS += \
       include/Game.hpp \
       include/GlobalSettings.hpp \
       include/IMenu.hpp \
       include/IPlayer.hpp \
       include/IPlayerVisualizer.hpp \
       include/Player.hpp \
       include/Visualizer.hpp

INCLUDEPATH += $$PWD/include

win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3
win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll

win32: INCLUDEPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include
win32: DEPENDPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include

win32: LIBS += -lopengl32
win32: LIBS += -lglfw3

linux: LIBS += -lglfw -lGL
