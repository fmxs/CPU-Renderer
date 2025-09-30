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


# ===== Demos: d00_min_loop =====
add_executable(d00_min_loop
  Demos/d00_min_loop/main.cpp
)

# 把当前工程的头路径塞进去（比如你后面要 include Core/… 时才会用到）
target_include_directories(d00_min_loop PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接 glfw
target_link_libraries(d00_min_loop PRIVATE glfw)

# macOS 还得补系统框架（和上面 demo 保持一致）
if(APPLE)
  target_link_libraries(d00_min_loop PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework OpenGL")
  target_compile_definitions(d00_min_loop PRIVATE GL_SILENCE_DEPRECATION=1)
endif()



# ===== Demos: d01_viewprobe =====
add_executable(d01_viewprobe
  Demos/d01_viewprobe/main.cpp
)

# 把当前工程的头路径塞进去（比如你后面要 include Core/… 时才会用到）
target_include_directories(d01_viewprobe PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接 glfw
target_link_libraries(d01_viewprobe PRIVATE glfw)

# macOS 还得补系统框架（和上面 demo 保持一致）
if(APPLE)
  target_link_libraries(d01_viewprobe PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework OpenGL")
  target_compile_definitions(d01_viewprobe PRIVATE GL_SILENCE_DEPRECATION=1)
endif()

