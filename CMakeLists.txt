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

set(GTESTS_DEFAULT_EXT "cc")

# List with filenames suitable for ${SOURCE_DIR}/*_test.${TESTS_EXT}
# This list can be extended here
list(APPEND GTESTS_TESTS_NAMES "ctors")
list(APPEND GTESTS_TESTS_NAMES "assign")

# List with tests' filenames in ${SOURCE_DIR}

# Parsing tests names to filenames suitable for
# ${SOURCE_DIR}/${TESTS_NAME}_test.${TESTS_EXT}
foreach(GTESTS_TEST_NAME IN LISTS GTESTS_TESTS_NAMES)
  list(APPEND GTESTS_TESTS_FILENAMES
    "${GTESTS_TEST_NAME}_test.${GTESTS_DEFAULT_EXT}")
endforeach()

# Here ${TESTS_FILENAMES} can be extended with other ${FILENAME} suitable for
# ${SOURCE_DIR}/${FILENAME}

# List of tests filepath. Tests can be located everywhere

# Making filepath for tests in ${SOURCE_DIR}
foreach(GTESTS_TEST_FILENAME IN LISTS GTESTS_TESTS_FILENAMES)
  list(APPEND GTESTS_TESTS_FILEPATHS
    "${SOURCE_DIR}/${GTESTS_TEST_FILENAME}")
endforeach()

# Here list of tests filepaths can be extendend

# Prepare list of tests' filepaths
string(REPLACE ";" ":" GTESTS_SOURCES ${GTESTS_TESTS_FILEPATHS})


add_library(test_utils STATIC EXCLUDE_FROM_ALL ${SOURCE_DIR}/test_utils.cc)
target_link_libraries(test_utils 
  PUBLIC gtest
)

add_executable(unittests EXCLUDE_FROM_ALL
  ${SOURCE_DIR}/string_ctors_test.cc
  ${SOURCE_DIR}/string_assign_test.cc
  ${SOURCE_DIR}/string_properties_test.cc
  ${SOURCE_DIR}/string_operations_test.cc
) 

target_link_libraries(unittests
  PUBLIC test_utils
  PUBLIC gtest
  PUBLIC gtest_main
)

gtest_discover_tests(unittests TEST_PREFIX "GTEST::" DISCOVERY_MODE PRE_TEST)
