set(TEST_EXECUTABLE_NAME StrTests)

add_executable(${TEST_EXECUTABLE_NAME} maingt.cpp nstring/nstring_ctors_gt.hpp nstring/nstring_ops_gt.hpp)

target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/../nstring)

target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE StrLib gtest::gtest)
