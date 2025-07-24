include(FetchContent)

FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        release-1.12.1
    )
FetchContent_MakeAvailable(googletest)


if(TARGET gtest AND TARGET gtest_main)
    message(STATUS "GoogleTest found, configuring tests")

    set(TEST_EXECUTABLE_NAME StringTests)

    file(GLOB_RECURSE TEST_EXECUTABLE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

    add_executable(${TEST_EXECUTABLE_NAME} ${TEST_EXECUTABLE_SOURCES})

    target_include_directories(${TEST_EXECUTABLE_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../nstring)

    target_link_libraries(${TEST_EXECUTABLE_NAME}
        PRIVATE StringLibrary gtest_main)

    enable_testing()
    add_test(NAME ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})

    set_property(TARGET gmock PROPERTY FOLDER "Thirdparty")
    set_property(TARGET gmock_main PROPERTY FOLDER "Thirdparty")
    set_property(TARGET gtest PROPERTY FOLDER "Thirdparty")
    set_property(TARGET gtest_main PROPERTY FOLDER  "Thirdparty")
else()
    message(WARNING "GoogleTest not available, skipping test target")
endif()
