add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/objects)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graphics)

target_sources(${CMAKE_PROJECT_NAME}
    PUBLIC
        main.cpp
)
