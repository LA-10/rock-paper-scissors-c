cmake_minimum_required(VERSION 3.8)

project(rock-paper-scissors-c VERSION 1.7)

# Collect all .c source files from src/
file(GLOB SOURCES "src/*.c")

# Create the executable from sources
add_executable(rock-paper-scissors-c ${SOURCES})

# Tell the compiler where to find header files
target_include_directories(rock-paper-scissors-c PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Copy asset and save folders into the build directory for runtime access
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
