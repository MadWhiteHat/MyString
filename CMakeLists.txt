cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

if (POLICY CMP0069)
  cmake_policy(SET CMP0069 NEW)
endif (POLICY CMP0069)

if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif (POLICY CMP0077)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

project(MyString LANGUAGES CXX C)

# DOWNLOAD ALL SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update all submodule
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMODULE_RESULT)
    if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with 
      ${GIT_SUBMODULE_RESULT}")
    endif() # GIT_SUBMODULE_RESULT != 0
  endif() # GIT_SUBMODULE
endif() # GIT_FOUND and .git folder exists

set(EXTENAL_MODULES_DIR "${PROJECT_SOURCE_DIR}/external")

message("${PROJECT_SOURCE_DIR}")

# Check all submodules
if(NOT EXISTS "${EXTENAL_MODULES_DIR}/googletest/CMakeLists.txt")
  message(FATAL_ERROR "The googletest modules was not downloaded!")
endif() # Cheking googletest module

set(SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
set(MAIN ${SOURCE_DIRECTORY}/main.cc)

add_executable(${PROJECT_NAME} ${MAIN})

# GoogleTest part
include(GoogleTest)
add_subdirectory(external/googletest)

set(GTESTS_DEFAULT_EXT "cc")

# List with filenames suitable for ${SOURCE_DIRECTORY}/*_test.${TESTS_EXT}
set(GTESTS_TESTS_NAMES "")
# This list can be extended here
list(APPEND GTESTS_TESTS_NAMES "ctors")

# List with tests' filenames in ${SOURCE_DIRECTORY}
set(GTESTS_TESTS_FILENAMES "")

# Parsing tests names to filenames suitable for
# ${SOURCE_DIRECTORY}/${TESTS_NAME}_test.${TESTS_EXT}
foreach(GTESTS_TEST_NAME IN LISTS GTESTS_TESTS_NAMES)
  list(APPEND GTESTS_TESTS_FILENAMES
    "${GTESTS_TEST_NAME}_test.${GTESTS_DEFAULT_EXT}")
endforeach()

# Here ${TESTS_FILENAMES} can be extended with other ${FILENAME} suitable for
# ${SOURCE_DIRECTORY}/${FILENAME}

# List of tests filepath. Tests can be located everywhere
set(GTESTS_TESTS_FILEPATHS "")

# Making filepath for tests in ${SOURCE_DIRECTORY}
foreach(GTESTS_TEST_FILENAME IN LISTS GTESTS_TESTS_FILENAMES)
  list(APPEND GTESTS_TESTS_FILEPATHS
    "${SOURCE_DIRECTORY}/${GTESTS_TEST_FILENAME}")
endforeach()

# Here list of tests filepaths can be extendend

# Preparing list of path for add_executable COMMAND
string(REPLACE ";" " " GTESTS_SOURCES ${GTESTS_TESTS_FILEPATHS})

add_executable(unittests ${GTESTS_SOURCES})
target_link_libraries(unittests gtest gtest_main)

gtest_discover_tests(unittests TEST_PREFIX "GTEST::" DISCOVERY_MODE PRE_TEST)
