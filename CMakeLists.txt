cmake_minimum_required(VERSION 3.0)

project(CHTTP)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}        # Include the root directory
    ${CMAKE_SOURCE_DIR}/inc # Include the 'include' directory where headers are stored
)

# Collect source files from src/ directory
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Print out all sources for debugging
message(STATUS "Sources: ${SOURCES}")

# Define the main executable
add_executable(main ${SOURCES})
