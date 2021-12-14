cmake_minimum_required(VERSION 2.8)

project(MagImacRun)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} lib/glimac/include lib/geometry/include lib/graphics/include lib/glm/include)

set(ALL_LIBRARIES glimac geometry graphic glm ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(lib/glimac)
add_subdirectory(lib/geometry)
add_subdirectory(lib/graphics)
add_subdirectory(lib/glm)

file(GLOB DIRECTORIES "app")
add_subdirectory(app)