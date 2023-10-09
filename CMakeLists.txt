cmake_minimum_required(VERSION 3.5.0)
project(3d_engine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wdeprecated-declarations")
set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/include)

add_executable(3d_engine
        config.hpp
        Buffer.hpp
        Buffer.cpp
        Engine.hpp
        Engine.cpp
        Shader.hpp
        Shader.cpp
        main.cpp)

find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(3d_engine glfw)
target_link_libraries(3d_engine GLEW::GLEW)