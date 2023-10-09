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

# ----------------------------------------------------------------------------------------------------------
# EXTERNAL DEPENDENCIES
# These are git projects (e,g, gtest, posutils, etc) using FetchContent
#
# For dependencies that do not integrate well with CMake
# Once a project XXXX is pulled using FetchContent, you get two variables:
# - <dependency>_SOURCE_DIR
# - <dependency>_BINARY_DIR
#
# If you fail to do this you compile WILL STILL WORK. However, you will incur the cost of 
# downloading the dependencies twice
#
# Note: 
# - dependencies that are fetched and built use "FetchContent_MakeAvailable(dep1 dep2 ... depN)"
# - header only dependencies (e.g. pegtl) need not be built. Use FetchContent_Populate
#
# The fetches are centralised here so they can be used from different projects
# AND 
# so there is only one place where the versions are set
# The final binaries for the dependencies are located in the user build folder
#
# KNOWN ISSUES:
# None
# ----------------------------------------------------------------------------------------------------------

# Fetch google test as a buildable library
macro(FetchContent_gtest)
  FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    GIT_SHALLOW    ON
    SOURCE_DIR     ${MG_THIRDPARTY_DIR}/gtest
  )
  # overrided options in the dependency
  option(INSTALL_GTEST "Enable installation of googletest." OFF)
  FetchContent_MakeAvailable(gtest)
endmacro(FetchContent_gtest)



# Fetch google benchmark as a buildable library
macro(FetchContent_benchmark)
  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.8.3
    GIT_SHALLOW    ON
    SOURCE_DIR ${MG_THIRDPARTY_DIR}/benchmark
  )
  # overrided options in the dependency
  option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)
  option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
  option(BENCHMARK_DOWNLOAD_DEPENDENCIES "Allow the downloading and in-tree building of unmet dependencies" OFF)
  option(BENCHMARK_ENABLE_INSTALL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)" OFF)
  option(BENCHMARK_INSTALL_DOCS "Enable installation of documentation." OFF)
  FetchContent_MakeAvailable(benchmark)
endmacro(FetchContent_benchmark)

# Fetch Microsoft GSL as a header only library
macro(FetchContent_GSL)
FetchContent_Declare(
    GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
    GIT_SHALLOW ON
    SOURCE_DIR ${MG_THIRDPARTY_DIR}/GSL
)
FetchContent_GetProperties(GSL)
if(NOT GSL_POPULATED)
  FetchContent_Populate(GSL)
endif()
endmacro(FetchContent_GSL)


#FetchContent_Declare(
#  gtest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  # GTest/GMock cannot be updated to later version as long as we are required to build with GCC 4.8.X
#  GIT_TAG        release-1.10.0
#  GIT_SHALLOW    ON
#  SOURCE_DIR     ${MG_THIRDPARTY_DIR}/gtest
#  PATCH_COMMAND  git apply "${MG_THIRDPARTY_DIR}/patches/gtest-0001-Enable-pic.patch" ||
#                 git apply "${MG_THIRDPARTY_DIR}/patches/gtest-0001-Enable-pic.patch" -R --check
#                 &&
#                 git apply "${MG_THIRDPARTY_DIR}/patches/gtest-0002-fix-error-dummy-may-be-used-uninitialized-Werror-may.patch" ||
#                 git apply "${MG_THIRDPARTY_DIR}/patches/gtest-0002-fix-error-dummy-may-be-used-uninitialized-Werror-may.patch" -R --check
