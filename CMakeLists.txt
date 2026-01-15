cmake_minimum_required(VERSION 4.1.0)

project(physics-simulation)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(gcem REQUIRED)

add_executable(${CMAKE_PROJECT_NAME})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(BUILD_TESTING)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:DEBUG>")
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:-fsanitize=address,undefined>")
target_link_options(${CMAKE_PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:-fsanitize=address,undefined>")

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wconversion
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sdl::sdl spdlog::spdlog gcem)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
