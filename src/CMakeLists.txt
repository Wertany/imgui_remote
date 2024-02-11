add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ..)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui imgui-ws)
