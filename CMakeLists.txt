cmake_minimum_required(VERSION 3.0)

project(CHTTP)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}  # Include the root directory
    Hashmap
    HTTP_status
    Network
    Routing
)

# Collect source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/main.c
    ${CMAKE_SOURCE_DIR}/Hashmap/*.c
    ${CMAKE_SOURCE_DIR}/HTTP_status/*.c
    ${CMAKE_SOURCE_DIR}/Network/*.c
    ${CMAKE_SOURCE_DIR}/Routing/*.c
)

# Define the main executable
add_executable(main ${SOURCES})
