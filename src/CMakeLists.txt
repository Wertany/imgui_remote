add_executable(${CMAKE_PROJECT_NAME} main.cpp
                                     web_server.cpp)
# target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_HOME_DIRECTORY}/external)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui implot imgui-ws)
