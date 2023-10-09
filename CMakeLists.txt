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

project("incubator")

enable_language( C CXX ASM )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This line does nothing as OPT_IN is default value anyway
# Added for the sake of raising awareness of the (currently inactive but promising in future) feature 
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE OPT_IN)

# ----------------------------------------------------------------------------------------------------------
# Build type
# ----------------------------------------------------------------------------------------------------------

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "RelWithDebInfo")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
# Setup Debug and RelWithDebInfo with the DEVELOP define enabling debugging
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -DK_ENGINEERING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DK_ENGINEERING")


# ----------------------------------------------------------------------------------------------------------
# Unit testing and coverage configuration and defaults
# Building Unit tests is enabled by default on all build types for all targets
# ----------------------------------------------------------------------------------------------------------
set(MG_ENABLE_UNITTESTS ON CACHE BOOL "Enable/Disable building unit tests")

# ----------------------------------------------------------------------------------------------------------
# General CMake settings affecting internal targets as well as imported/fetched dependencies
# ----------------------------------------------------------------------------------------------------------

# Libraries are always static but dependencies should be build statically by default as well.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")

# Enable PIC globally to simplify maintenance for third party libraries.
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)

# ----------------------------------------------------------------------------------------------------------
# Set up project paths
# ----------------------------------------------------------------------------------------------------------
set(MG_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party CACHE PATH "Location of third-party libraries")
set(MG_ASSETS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/assets/ CACHE PATH "Location of MG4NEWS assets library")
set(MG_BASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mg-base CACHE PATH "Location of base library")

# ----------------------------------------------------------------------------------------------------------
# CMake module paths
# ----------------------------------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules
)

# ----------------------------------------------------------------------------------------------------------
# CMake modules
# ----------------------------------------------------------------------------------------------------------
include(ExternalProject)
include(CMakePackageConfigHelpers)

# Modules for MG4NEWS Targets
include(MgTargetDefaults)

# EXTERNAL DEPENDENCIES
# These are:
# - Pulled from git using FetchContent
# - Stored in the "third-party" folder
#
# The macro for a dependency XXXX is FetchContent_XXXX
# Once a project XXXX is pulled using FetchContent_XXXX, you get:
# - XXXX_SOURCE_DIR which can be used in include paths
# - the library can be added to target_link_libraries()
#
# All of the pulled dependencies are written to MG_THIRDPARTY_DIR. They are pulled once by the first use. 
# There are not destroyed when the project build directory is deleted.
#
# NOTE: ONLY FETCH WHAT YOU ACTUALLY NEED. If any one of these requires a 3rd party acknowledgement it will be generated by
# fetching it. If I dont use something I dont want to add an acknowledgement to the the release notes.
#
# To debug the downloading of dependencies put this before the fetches:
# set(FETCHCONTENT_QUIET off)
include(FetchContent)
include(MgThirdPartyFetchers)

# ----------------------------------------------------------------------------------------------------------
# Include the directories that define targets
# ----------------------------------------------------------------------------------------------------------
add_subdirectory(libraries/mgbase)

# ----------------------------------------------------------------------------------------------------------
# Code Coverage Reports
# ----------------------------------------------------------------------------------------------------------
if (MG_ENABLE_COVERAGE)
    # Generate coverage reports only when it is build as its own project.
    # Note that, when the super-project is consumed via "add_subdirectory",
    # the top level project should be the one invoking the coverage report tool
    if(PROJECT_IS_TOP_LEVEL AND MG_ENABLE_UNITTESTS)

        find_program(GCOVR_BIN gcovr)
        if(GCOVR_BIN MATCHES "gcovr$")
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage_reports)
            # Note that the command is invoked with current binary folder as root folder,
            # in order to support out of source builds.
            # The source files folders and coverage data files are indicated with filters
            add_custom_target(coverage-report
                ALL
                COMMENT "Generating coverage report for ${CMAKE_CURRENT_SOURCE_DIR}"
                COMMAND ${GCOVR_BIN} -k -r ${CMAKE_BINARY_DIR} --print-summary
                    --html-details=${CMAKE_BINARY_DIR}/coverage_reports/${PROJECT_NAME}.html
                    --xml=${CMAKE_BINARY_DIR}/coverage_reports/${PROJECT_NAME}.xml --xml-pretty
                    --gcov-filter=${CMAKE_BINARY_DIR}
                    # library folders
                    --filter ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mgbase
                    --exclude=${CMAKE_CURRENT_SOURCE_DIR}/libraries/mgbase/third_party
                    --exclude=${CMAKE_CURRENT_SOURCE_DIR}/libraries/mgbase/unittests
                COMMENT "Coverage report available in ${CMAKE_BINARY_DIR}/coverage_reports"
            )

            # ensure that the report is triggered after running the unit tests
            add_dependencies(coverage-report run-mgbase-unittests)
        else()
            MESSAGE(WARNING "gcovr required for coverage reporting, but not found!")
            MESSAGE(WARNING "No coverage report will be generated!")
        endif()
    else()
        MESSAGE(WARNING "Coverage is disabled:")
        MESSAGE(WARNING "   Top Level: ${PROJECT_IS_TOP_LEVEL}")
        MESSAGE(WARNING "   Testing Enabled: ${MG_ENABLE_UNITTESTS}")
    endif()
endif()
