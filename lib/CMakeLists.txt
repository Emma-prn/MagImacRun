include_directories(include)

file(GLOB_RECURSE GEO_SRC_FILES geometry/src/*.cpp)
file(GLOB_RECURSE GEO_HPP_FILES geometry/include/*.hpp)
add_library(geometry ${GEO_SRC_FILES} ${GEO_HPP_FILES})
target_include_directories(geometry PRIVATE "include")

file(GLOB_RECURSE GLI_SRC_FILES glimac/src/*.cpp glimac/src/*.h)
file(GLOB_RECURSE GLI_HPP_FILES glimac/include/*.hpp)
add_library(glimac ${GLI_SRC_FILES} ${GLI_HPP_FILES})
target_include_directories(glimac PRIVATE "include")

file(GLOB_RECURSE GRA_SRC_FILES graphics/src/*.cpp)
file(GLOB_RECURSE GRA_HPP_FILES graphics/include/*.hpp)
add_library(graphics ${GRA_SRC_FILES} ${GRA_HPP_FILES})
target_include_directories(graphics PRIVATE "include")

file(GLOB_RECURSE GLM_HPP_FILES glm/include/*.hpp)
add_library(glm ${GLM_HPP_FILES})
target_include_directories(glm PRIVATE "include")