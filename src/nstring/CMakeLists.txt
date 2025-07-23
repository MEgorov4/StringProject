set(STRING_LIBRARY_NAME NStringLib)

file(GLOB_RECURSE STRING_LIBRARY_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(${STRING_LIBRARY_NAME} STATIC ${STRING_LIBRARY_SOURCES})

if (MSVC)
    message("Setup msvc flags")
    target_compile_options(${STRING_LIBRARY_NAME} PRIVATE /W4 /preissive /WX )
else()
    message("Setup gcc/clang flags")
    target_compile_options(${STRING_LIBRARY_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Woverflow -Wshadow -Werror)
endif()
