# Need for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
cmake_minimum_required(VERSION 3.21)
project(StringProject VERSION 1.0 LANGUAGES CXX)

# Lang&Env setup
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    message("Setup msvc flags")
    add_compile_options(/W4 /preissive /WX )
else()
    message("Setup gcc/clang flags")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Woverflow -Wshadow -Werror)
endif()

# Pick packages
include(FetchContent)

FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        release-1.8.1
    )

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src)

include(GoogleTest)
