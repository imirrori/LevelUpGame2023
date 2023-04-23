TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
       src/Game.cpp \
       src/MainMenu.cpp \
       src/Settings.cpp \
       src/Visualizer.cpp \
       App/main.cpp

HEADERS += \
       include/MainMenu.hpp \
       include/interface/IEntity.hpp \
       include/interface/IMenu.hpp \
       include/interface/IPlayer.hpp \
       include/interface/ISettings.hpp \
       include/Game.hpp \
       include/PlayerStub.hpp \
       include/Settings.hpp \
       include/Visualizer.hpp

INCLUDEPATH += $$PWD/include

win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3
win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll

win32: INCLUDEPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include
win32: DEPENDPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include

win32: LIBS += -lopengl32
win32: LIBS += -lglfw3

linux: LIBS += -lglfw -lGL
