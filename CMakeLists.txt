cmake_minimum_required(VERSION 4.1.0)

project(physics-simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(lib/SDL3-3.2.24 EXCLUDE_FROM_ALL)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/object.cpp
    src/exceptions.cpp
    src/objects/rectangle.cpp
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wconversion
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)
