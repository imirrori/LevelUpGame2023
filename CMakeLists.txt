cmake_minimum_required(VERSION 3.24)
project(Mario)

set(CMAKE_CXX_STANDARD 20)

# Add the SFML library
include(FetchContent)

FetchContent_Declare(SFML
                     GIT_REPOSITORY https://github.com/SFML/SFML.git
                     GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

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

    Game/src/Entity.cpp
    Game/src/Game.cpp
    Game/src/Level.cpp
    Game/src/Map.cpp
    Game/src/EntityCoin.cpp
    Game/src/EntityMushroom.cpp
    Game/src/EntityPipe.cpp
    Game/src/EntityBlock.cpp
    Game/src/EntityStar.cpp
    Game/src/KeyManager.cpp
    Game/src/MainMenu.cpp
    Game/src/Settings.cpp
    Game/src/Visualizer.cpp

    )

set(HEADER_FILES
    lib/STBI/stbi_image.h

    Game/include/interface/IEntity.hpp
    Game/include/interface/ISettings.hpp
    Game/include/interface/IVizMap.hpp
    Game/include/interface/IVizMenu.hpp
    Game/include/interface/IVizPlayer.hpp

    Game/include/Game.hpp
    Game/include/Entity.hpp
    Game/include/Level.hpp
    Game/include/Map.hpp
    Game/include/EntityCoin.hpp
    Game/include/EntityMushroom.hpp
    Game/include/EntityPipe.hpp
    Game/include/EntityBlock.hpp
    Game/include/EntityStar.hpp
    Game/include/KeyManager.hpp
    Game/include/MainMenu.hpp
    Game/include/PlayerStub.hpp
    Game/include/Settings.hpp
    Game/include/Visualizer.hpp
    )

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