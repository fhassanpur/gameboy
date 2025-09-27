cmake_minimum_required(VERSION 3.16)
project(gameboy)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(lib/SDL3 EXCLUDE_FROM_ALL)

# Automatically include all .c files in the src/ directory
file(GLOB SOURCES "src/*.c")

# Create your game executable target as usual
add_executable(gameboy ${SOURCES})

# Include the include/ directory
target_include_directories(gameboy PRIVATE include)

# Link to the actual SDL3 library.
target_link_libraries(gameboy PRIVATE SDL3::SDL3)