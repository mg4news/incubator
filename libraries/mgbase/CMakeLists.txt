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

project(mgbase VERSION 0.0.1)

# ----------------------------------------------------------------------------------------------------------
# Fetch the dependencies using the FetchContent macros
# FetchContent_xxx()
# If building the library standalone then the 3rd party directory
# will need to be defined, i.e. where the fetch content is placed. 
# ----------------------------------------------------------------------------------------------------------
if(NOT DEFINED MG_THIRDPARTY_DIR)
  set(MG_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
endif(NOT DEFINED MG_THIRDPARTY_DIR)
FetchContent_GSL()

# ----------------------------------------------------------------------------------------------------------
# mgbase Library
# ----------------------------------------------------------------------------------------------------------

set(MGBASE_HDR
  include/mgbase/base.hpp
  include/mgbase/assert.hpp
  include/mgbase/sem.hpp
  include/mgbase/console.hpp
)

set(MGBASE_SRC
  ${MGBASE_HDR}

  src/assert.cpp
  src/idempotent.cpp
  src/console.cpp
)

add_library(${PROJECT_NAME} STATIC ${MGBASE_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  POSITION_INDEPENDENT_CODE ON
)

# set up defaults for the target
mg_target_compile_definitions(${PROJECT_NAME})
mg_target_compile_warnings(${PROJECT_NAME})
mg_target_compile_lto(${PROJECT_NAME})
mg_target_compile_asan(${PROJECT_NAME})
mg_target_handle_code_coverage(${PROJECT_NAME})

# Debug
include(CMakePrintHelpers)
cmake_print_variables(mgbase_VERSION)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
  MGBASE_VERSION="${mgbase_VERSION}"
  MGBASE_VERSION_MAJOR=${mgbase_VERSION_MAJOR}
  MGBASE_VERSION_MINOR=${mgbase_VERSION_MINOR}
  MGBASE_VERSION_PATCH=${mgbase_VERSION_PATCH}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME}
)

# ----------------------------------------------------------------------------------------------------------
# Unit testing
# ----------------------------------------------------------------------------------------------------------
if (MG_ENABLE_UNITTESTS)
    add_subdirectory(unittests)
endif()
