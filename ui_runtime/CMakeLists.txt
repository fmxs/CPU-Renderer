cmake_minimum_required(VERSION 3.20)
project(ui_runtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# macOS: 安静点
if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION=1)
endif()

include(FetchContent)
# 固定 GLFW 版本
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# 你要是看它 warning 闹心，可以加：set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

add_executable(ui-demo
  Demo/main.cpp
  App/UApplication.cpp
  Core/Time.cpp
  Core/Log.cpp
  Input/Input.cpp
  Render/DrawList.cpp
  Render/Renderer2D_GL.cpp
)

target_include_directories(ui-demo PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# 只对“我们自己”的目标开 -Wall/-Wextra/-Werror；不污染 glfw
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  target_compile_options(ui-demo PRIVATE -Wall -Wextra -Werror)
endif()

target_link_libraries(ui-demo PRIVATE glfw)

# macOS 框架
if(APPLE)
  target_link_libraries(ui-demo PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework OpenGL")
endif()

# ===== Demos: d00_boot =====
add_executable(demo-d00-boot
  Demos/d00_boot/main.cpp
  Input/Input.cpp
  Core/Time.cpp
  Core/Log.cpp
  Render/DrawList.cpp
  Render/Renderer2D_GL.cpp
)
target_include_directories(demo-d00-boot PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(demo-d00-boot PRIVATE glfw)
if(APPLE)
  target_link_libraries(demo-d00-boot PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework OpenGL")
endif()

# ===== Tools: tiny_probe =====
add_executable(tiny_probe
  Demos/tiny_probe/main.cpp
)

# 关键一行：让 glfw 的头路径/编译定义传过来
target_link_libraries(tiny_probe PRIVATE glfw)

# macOS 还需要这些系统框架（和你 d00 保持一致）
if(APPLE)
  target_link_libraries(tiny_probe PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework OpenGL")
  target_compile_definitions(tiny_probe PRIVATE GL_SILENCE_DEPRECATION=1)
endif()

# 如果 tiny_probe 需要包含你工程里的头（比如 Core/…），再开这句更稳：
target_include_directories(tiny_probe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

