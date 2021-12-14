file(GLOB HEADER_FILES *.hpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

add_executable(app main.cpp ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(app ${ALL_LIBRARIES})

target_compile_features(app PRIVATE cxx_std_11)
target_compile_options(app PRIVATE -Wall -O2)

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})