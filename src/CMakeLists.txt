add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/objects)

target_sources(${CMAKE_PROJECT_NAME}
    PUBLIC
        main.cpp
        window.cpp
)
