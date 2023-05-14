TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
       src/Game.cpp \
       src/KeyManager.cpp \
       src/MainMenu.cpp \
       src/Map.cpp \
       src/Settings.cpp \
       src/Texture.cpp \
       src/Visualizer.cpp \
       App/main.cpp

HEADERS += \
       libs/STBI/stbi_image.h \
       include/KeyManager.hpp \
       include/MainMenu.hpp \
       include/Map.hpp \
       include/interface/IEntity.hpp \
       include/interface/ISettings.hpp \
       include/Game.hpp \
       include/PlayerStub.hpp \
       include/Settings.hpp \
       include/Visualizer.hpp \
       include/Texture.hpp \
       include/interface/IVizMap.hpp \
       include/interface/IVizMenu.hpp \
       include/interface/IVizPlayer.hpp \
       include/interface/Texture.hpp

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/libs/STBI

win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3
win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll

win32: INCLUDEPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include
win32: DEPENDPATH += $$PWD/libs/glfw-3.3.8.bin.WIN64/include

win32: LIBS += -lopengl32
win32: LIBS += -lglfw3

linux: LIBS += -lglfw -lGL
