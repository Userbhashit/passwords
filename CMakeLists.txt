cmake_minimum_required(VERSION 3.10)
project(password_project C)

# Generate compile_commands.json in project root
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Place compile_commands.json in project root instead of build/
set(CMAKE_COMPILE_COMMANDS_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Find all source files in src/
file(GLOB SOURCES "src/*.c")

# Add include/ folder to compiler search path 
include_directories(${PROJECT_SOURCE_DIR}/header)

# Create executable from all .c files
add_executable(password ${SOURCES})

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)

