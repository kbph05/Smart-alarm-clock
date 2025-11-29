# CMake Build Configuration for root of project
cmake_minimum_required(VERSION 3.18)
project(Smart-alarm-clock VERSION 1.0 DESCRIPTION "Final project for ENSC 351: Smart alarm clock " LANGUAGES C)

# Compiler options (inherited by sub-folders)
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Werror -Wextra) #-Wpedantic removed for useage of 0b for binary numbers
add_compile_options(-fdiagnostics-color)

# Enable address sanitizer
# (Comment this out to make your code faster)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Enable PThread library for linking
add_compile_options(-pthread)
add_link_options(-pthread)

# What folders to build
add_subdirectory(hal)  
add_subdirectory(app)

