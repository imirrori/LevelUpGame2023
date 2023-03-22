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

# Compile external dependencies
add_subdirectory(external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if (INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif (INCLUDE_DISTRIB)


include_directories(
        external/AntTweakBar-1.16/include/
        external/glfw-3.1.2/include/
        external/glm-0.9.7.1/
        external/glew-1.13.0/include/
        external/assimp-3.0.1270/include/
        external/bullet-2.81-rev2613/src/
        .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
    )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)


add_subdirectory(Game)

############################################################
# Create a library
############################################################

# Generate the shared library from the library sources


#add_library(Mario_Lib SHARED
#            Game/src/Game.cpp
#
#            )
#
#
#add_library(mario::lib ALIAS Mario_Lib)
#
#target_include_directories(Mario_Lib
#                           PUBLIC
#                           ${PROJECT_SOURCE_DIR}/Game/include
#                           )


# Add an executable with the above sources

include_directories(Game/include)

set(SOURCE_FILES
    Game/App/main.cpp
    Game/src/Game.cpp
    common/shader.cpp

    Game/src/SimpleFragmentShader.fragmentshader
    Game/src/SimpleVertexShader.vertexshader
    )

set(HEADER_FILES
    Game/include/Game.hpp
    common/shader.hpp
    )

add_executable(Mario ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Mario PRIVATE
                      ${ALL_LIBS}
                      )

set_target_properties(Mario PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${Mario_SOURCE_DIR}/bin")
create_target_launcher(Mario WORKING_DIRECTORY "${Mario_SOURCE_DIR}/bin")
create_default_target_launcher(Mario WORKING_DIRECTORY "${Mario_SOURCE_DIR}/bin")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*")
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$")

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")

    add_custom_command(
            TARGET Mario POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Mario${CMAKE_EXECUTABLE_SUFFIX}"
            "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    )


elseif (${CMAKE_GENERATOR} MATCHES "Xcode")

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
