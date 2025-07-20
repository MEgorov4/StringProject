# Need for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
cmake_minimum_required(VERSION 3.21)
project(StringProject VERSION 1.0 LANGUAGES CXX)

# Lang&Env setup
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    message("Setup msvc flags")
    add_compile_options(/W4 /WX)
else()
    message("Setup gcc/clang flags")
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# Pick packages
find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(src)

include(GoogleTest)
