cmake_minimum_required(VERSION 3.8)

project(rock-paper-scissors-c VERSION 1.7)

# Find Python 3 and its development files
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Collect all .c source files from src/
file(GLOB SOURCES "src/*.c")

# Create the executable
add_executable(rock-paper-scissors-c ${SOURCES})

# Include your headers
target_include_directories(rock-paper-scissors-c PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Link Python (for using Python C API)
target_include_directories(rock-paper-scissors-c PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(rock-paper-scissors-c PRIVATE ${Python3_LIBRARIES})

# Only copy assets if it's not already inside build/
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
