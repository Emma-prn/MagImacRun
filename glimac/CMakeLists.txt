add_library(glimac)
add_library(glimac::glimac ALIAS glimac)

target_include_directories(glimac PUBLIC include)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
target_sources(glimac PRIVATE ${SRC_FILES})

add_subdirectory(third-party/glm)
target_link_libraries(glimac PUBLIC glm::glm)

find_package(GLEW REQUIRED)
target_include_directories(glimac PUBLIC ${GLEW_INCLUDE_DIR})
target_include_directories(glimac PUBLIC src)
target_link_libraries(glimac PUBLIC ${GLEW_LIBRARIES})