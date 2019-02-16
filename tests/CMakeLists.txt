cmake_minimum_required(VERSION 3.12)
project(FurgbolCoreTests)

enable_testing()
configure_file("CMakeLists.txt.in" "googletest-download/CMakeLists.txt")

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)

set(FurgbolCore_DIR "../dist/lib/cmake")
find_package(FurgbolCore REQUIRED)

include_directories("../include")

add_executable(data_management_test "first_test.cpp")
target_link_libraries(data_management_test gtest_main FurgbolCore::data_management)
add_test(NAME data_management_test COMMAND data_management_test)