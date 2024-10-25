cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# Useful for LSPs like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(
    "chauder"
    C
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Adding address sanitizer")
    add_compile_options(-g -fsanitize=address -DVERBOSE=5)
    add_link_options(-lasan)
endif()

find_library(glfw glfw)
link_libraries(glfw)

# Flags for Better/Safer code
add_compile_options(-Wall -Werror -Wextra -Wshadow)

# Define the glad target for libglad.so 
add_subdirectory(glad/)
link_libraries(glad)

# Define the chauder target for libchauder.so 
add_subdirectory(src/)
link_libraries(chauder)

# Define the target in the examples/ directory and link chauder and glad to them
add_subdirectory(example/)
