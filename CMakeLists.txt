cmake_minimum_required(VERSION 3.26)
project(main C CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(SDL3 REQUIRED CONFIG)

add_executable(main)

target_sources(main
PRIVATE
    main.cpp
    src/init.cpp
    src/math.cpp
    src/camera.cpp
    src/renderer.cpp
    src/parseobj.cpp
    src/geometry.cpp
)

target_link_libraries(main SDL3::SDL3)
