cmake_minimum_required (VERSION 3.10)
project(imgui_remote)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(external/imgui-ws)
add_subdirectory(external/implot)