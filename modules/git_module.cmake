macro(fetch_git_submodules)
# DOWNLOAD ALL SUBMODULES
  find_package(Git QUIET)
  # .git exists at top level
  if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
# Update all submodule
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
      message(STATUS "Submodule update")
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
        --recursive --remote
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
      if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with 
        ${GIT_SUBMODULE_RESULT}")
      endif() # GIT_SUBMODULE_RESULT != 0
    endif() # GIT_SUBMODULE
  endif() # GIT_FOUND and .git folder exists

endmacro() #fetch_git_submodules

macro(check_git_submodule SUBMODULE MODULES_DIR)
  if(NOT EXISTS "${MODULES_DIR}/${SUBMODULE}/CMakeLists.txt")
    message(FATAL_ERROR "The ${SUBMODULE} submodule was not downloaded or not"
      " correctly setup for cmake!")
endif() # Cheking module
endmacro() # check_git_submodule
