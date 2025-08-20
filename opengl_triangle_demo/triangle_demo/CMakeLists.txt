enable_language(C)

cmake_minimum_required(VERSION 3.15)
project(ColoredTriangle CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 找 OpenGL
find_package(OpenGL REQUIRED)

# GLFW 在 /opt/homebrew 安装的
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h /opt/homebrew/include /usr/local/include)
find_library(GLFW_LIB glfw /opt/homebrew/lib /usr/local/lib)

include_directories(
  ${GLFW_INCLUDE_DIR}
  include
)

add_executable(tri
  src/main.cpp
  src/gl.c
)

target_link_libraries(tri
  ${GLFW_LIB}
  ${OPENGL_gl_LIBRARY}
)

if(APPLE)
  target_link_libraries(tri
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
  )
endif()

