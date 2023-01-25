cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

project(MyString LANGUAGES CXX C)

# locating modules dir
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/")
include(git_module)
fetch_git_submodules()

set(EXTENAL_MODULES_DIR "${PROJECT_SOURCE_DIR}/external")

check_git_submodule("googletest" "${EXTENAL_MODULES_DIR}")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(MAIN ${SOURCE_DIR}/main.cc)

add_executable(${PROJECT_NAME} ${MAIN})

# GoogleTest part

# Minimal standard for GoogleTest
set(CMAKE_CXX_STANDARD_REQUIRED 14)

include(GoogleTest)
add_subdirectory(external/googletest)

add_library(test_utils STATIC EXCLUDE_FROM_ALL ${SOURCE_DIR}/test_utils.cc)
target_link_libraries(test_utils 
  PUBLIC gtest
)

add_executable(unittests EXCLUDE_FROM_ALL
  ${SOURCE_DIR}/string_ctors_test.cc
  ${SOURCE_DIR}/string_assign_test.cc
  ${SOURCE_DIR}/string_properties_test.cc
  ${SOURCE_DIR}/string_insert_test.cc
  ${SOURCE_DIR}/string_erase_test.cc
  ${SOURCE_DIR}/string_simple_operations_test.cc
  ${SOURCE_DIR}/string_append_test.cc
  ${SOURCE_DIR}/string_compare_test.cc
  ${SOURCE_DIR}/string_replace_test.cc
  ${SOURCE_DIR}/string_find_test.cc
)

target_link_libraries(unittests
  PUBLIC test_utils
  PUBLIC gtest
  PUBLIC gtest_main
)

gtest_discover_tests(unittests TEST_PREFIX "GTEST::" DISCOVERY_MODE PRE_TEST)
