cmake_minimum_required(VERSION 2.8)

project(MagImacRun)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

add_subdirectory(glimac)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

file(GLOB HEADER_FILES app/*.hpp)
file(GLOB_RECURSE SHADER_FILES app/shaders/*.glsl)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS app/*.cpp)

add_executable(app ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_include_directories(app PRIVATE app/geometry/include app/graphics/include)
target_link_libraries(app PRIVATE ${ALL_LIBRARIES})

target_compile_features(app PRIVATE cxx_std_17)
target_compile_options(app PRIVATE -Wall -O2)

file(COPY app/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})