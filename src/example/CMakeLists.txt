set(MAIN_EXECUTABLE_NAME StrExample)

add_executable(${MAIN_EXECUTABLE_NAME} main.cpp)

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../nstring)
target_link_libraries(${MAIN_EXECUTABLE_NAME}
    PRIVATE
    NStringLib)



