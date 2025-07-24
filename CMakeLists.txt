cmake_minimum_required(VERSION 3.16)
project(StringProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT StringExample)

set_property(TARGET StringLibrary PROPERTY FOLDER "String")
set_property(TARGET StringExample PROPERTY FOLDER "String")
set_property(TARGET StringTests PROPERTY FOLDER "Tests")
