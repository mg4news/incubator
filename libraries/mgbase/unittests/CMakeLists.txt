# =============================================================================
# This is free and unencumbered software released into the public domain.
# 
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any means
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# This is a simplified version of UNLICENSE. For more information,
# please refer to <http://unlicense.org/>
# =============================================================================

# ----------------------------------------------------------------------------------------------------------
# Using a minimum of 3.24 for VSCode generators

# ----------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(mgbase-unittests)

# ----------------------------------------------------------------------------------------------------------
# Target dependencies Dependencies
# 3rd party directory already defined in parent cmake file
# ----------------------------------------------------------------------------------------------------------
FetchContent_gtest()

# ----------------------------------------------------------------------------------------------------------
# Executable
# ----------------------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
  main.cpp
  idempotent.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

# set up kauai defaults for the target
mg_target_compile_definitions(${PROJECT_NAME})

# warning for missing include dirs does not work with GTest >= 1.10,
# because it adds folder for backward compatibility
set(MG_WARNING_DISABLE_MISSING_INCLUDE_DIRS ON)
mg_target_compile_warnings(${PROJECT_NAME})
unset(MG_WARNING_DISABLE_MISSING_INCLUDE_DIRS)

mg_target_compile_lto(${PROJECT_NAME})
mg_target_compile_asan(${PROJECT_NAME})
mg_target_handle_code_coverage(${PROJECT_NAME})

# DEBUG
#include(CMakePrintHelpers)
#cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
#cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  mgbase
  gtest
)

add_custom_target(run-${PROJECT_NAME}
  ALL
  COMMENT "Running mgbase unitests"
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
)
