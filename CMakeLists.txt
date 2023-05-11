cmake_minimum_required(VERSION 3.24)
project(Mario)

set(CMAKE_CXX_STANDARD 20)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


find_package(spdlog REQUIRED)


find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    message(STATUS "OpenGL found")
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
else ()
    message(STATUS "OpenGL not found")
endif ()

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif ()

if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()

if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Compile external dependencies

# Box2D
set(box2d_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/Box2D/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/Box2D ${PROJECT_BINARY_DIR}/Box2D)

# GLEW
set(GLEW_INCLUDE_DIRS /opt/homebrew/Cellar/glew/2.2.0_1/include)

find_package(GLEW REQUIRED)


include_directories(
        /opt/homebrew/Cellar/glew/2.2.0_1/include
        /opt/hombrew/spdlog/include
        lib/glm
        lib/box2d/include
        lib/box2d/extern/glad/include
        lib/box2d/extern/glfw/include
        .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW::GLEW
    box2d
    spdlog::spdlog_header_only

    )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

set(SOURCE_FILES
    lib/STBI/stbi_image.cpp
    Game/src/Input.cpp
    Game/src/Game.cpp
    Game/src/Level.cpp
    Game/src/Map.cpp
    Game/src/Entity/EntityStepBlock.cpp
    Game/src/Entity/EntityCoin.cpp
    Game/src/Entity/EntityMushroom.cpp
    Game/src/Entity/EntityPipe.cpp
    Game/src/Entity/EntityBlock.cpp
    Game/App/main.cpp
    Game/src/Entity/EntityGround.cpp
    Game/src/Entity/EntityMario.cpp
    Game/src/View.cpp
    Game/src/Texture.cpp
    Game/src/Graphics/Render.cpp
    Game/src/Graphics/Shader.cpp
    Game/src/ContactListener.cpp
    Game/src/EventSystem.cpp
    Game/src/Entity/EntityCoinBlock.cpp
    Game/src/MapParser.cpp
    Game/src/Sprite.cpp
    Game/src/GameState.cpp
    Game/src/LoggerTest.cpp

    )

set(HEADER_FILES
    lib/STBI/stbi_image.h
    Game/include/Game.hpp
    Game/include/Input.hpp
    Game/include/interface/IEntity.hpp
    Game/include/interface/IEventHandler.hpp
    Game/include/interface/ILevel.hpp
    Game/include/Entity/Entity.hpp
    Game/include/Level.hpp
    Game/include/Map.hpp
    Game/include/Entity/EntityStepBlock.hpp
    Game/include/Entity/EntityCoin.hpp
    Game/include/Entity/EntityMushroom.hpp
    Game/include/Entity/EntityPipe.hpp
    Game/include/Entity/EntityBlock.hpp
    Game/include/Entity/EntityGround.hpp
    Game/include/Entity/EntityMario.hpp
    Game/include/View.hpp
    Game/include/Texture.hpp
    Game/include/Graphics/Render.hpp
    Game/include/Graphics/Shader.hpp
    Game/include/ContactListener.hpp
    Game/include/EventSystem.hpp
    Game/include/Entity/EntityCoinBlock.hpp
    Game/include/interface/IMap.hpp
    Game/include/MapParser.hpp
    Game/include/Sprite.hpp
    Game/include/GAME_STATES.hpp
    Game/include/interface/IProcessInput.hpp
    Game/include/GameState.hpp
    Game/include/logtest.hpp)


############################################################
# Create a MENU library
############################################################

#set(SOURCE_FILES_MENU
#    Game/src/Menu/GameMenu.cpp
#    Game/src/Menu/Animator.cpp
#    Game/src/Menu/AssetManager.cpp
#    Game/src/Menu/MainMenu.cpp
#    Game/src/Menu/MenuHandler.cpp
#    )
#
#set(HEADER_FILES_MENU
#    Game/include/Menu/GameMenu.hpp
#    Game/include/Menu/Animator.hpp
#    Game/include/Menu/AssetManager.hpp
#    Game/include/Menu/MainMenu.hpp
#    Game/include/Menu/MenuHandler.hpp
#    )
#
#add_library(Mario_Menu_Lib SHARED
#            ${SOURCE_FILES_MENU}
#            ${HEADER_FILES_MENU}
#            )
#
#add_library(mario::menu::lib ALIAS Mario_Menu_Lib)
#
#target_include_directories(Mario_Menu_Lib
#                           PUBLIC
#                           ${PROJECT_SOURCE_DIR}/Game/include
#                           ${PROJECT_SOURCE_DIR}/lib
#                           )


############################################################
# Create a library
############################################################

# Generate the shared library from the library sources


add_library(Mario_Lib SHARED
            ${SOURCE_FILES}
            ${HEADER_FILES}
            )


add_library(mario::lib ALIAS Mario_Lib)

target_include_directories(Mario_Lib
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/Game/include
                           ${PROJECT_SOURCE_DIR}/lib
                           ${box2d_INCLUDE_DIRS}
                           ${PROJECT_SOURCE_DIR}/lib/STBI
                           ${PROJECT_SOURCE_DIR}/lib/glm


                           )

target_link_libraries(Mario_Lib
                      PRIVATE
                      ${ALL_LIBS}
                      #                      mario::menu::lib
                      )


# Add an executable with the above sources

include_directories(Game/include)


add_subdirectory(Game)

add_executable(Mario Game/App/main.cpp)


add_custom_command(
        TARGET Mario POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory
        ${PROJECT_SOURCE_DIR}/Game/Resources/audio
        $<TARGET_FILE_DIR:Mario>/audio
        VERBATIM)

add_custom_command(
        TARGET Mario POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory
        ${PROJECT_SOURCE_DIR}/Game/Resources/font
        $<TARGET_FILE_DIR:Mario>/font
        VERBATIM
)

add_custom_command(
        TARGET Mario POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory
        ${PROJECT_SOURCE_DIR}/Game/Resources/image
        $<TARGET_FILE_DIR:Mario>/image
        VERBATIM
)


target_include_directories(Mario
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/Game/include
                           ${PROJECT_SOURCE_DIR}/lib
                           ${box2d_INCLUDE_DIRS}
                           ${PROJECT_SOURCE_DIR}/lib/STBI
                           ${PROJECT_SOURCE_DIR}/lib/glm

                           )

target_link_libraries(Mario PRIVATE
                      mario::lib
                      )

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Mario POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Mario> $<TARGET_FILE_DIR:Mario>
                       COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS Mario DESTINATION release)