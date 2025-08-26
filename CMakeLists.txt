cmake_minimum_required(VERSION 3.20)

project(c_ogl_wrapper)

find_package(OpenGL REQUIRED)

set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.4)
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/_deps/glfw-build EXCLUDE_FROM_ALL)

add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
if (NOT TARGET glad::glad)
    add_library(glad::glad ALIAS glad)
endif ()

add_library(coglw STATIC
        src/window.c
        src/glad_wrapper.c
        src/shader.c
        src/vertex_buffer.c
        src/vertex_array.c
        src/gl_info.c
)

target_include_directories(coglw PUBLIC
        include
)

target_link_libraries(coglw PUBLIC glad glfw OpenGL::GL)

target_compile_options(coglw PRIVATE -Wall -Wextra -Wpedantic)

add_subdirectory(examples/triangle)
