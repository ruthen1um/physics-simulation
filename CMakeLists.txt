cmake_minimum_required(VERSION 4.1.0)

project(physics-simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL3 REQUIRED)
find_package(spdlog REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/object.cpp
    src/exceptions.cpp
    src/window.cpp
    src/objects/rectangle.cpp
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wconversion
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sdl::sdl spdlog::spdlog)
