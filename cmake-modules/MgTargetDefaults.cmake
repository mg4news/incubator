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


#! mg_target_compile_definitions : sets private compile definitions for the given target
# This function sets configuration dependent definitions that affect all targets
function(mg_target_compile_definitions TARGET_NAME)
    string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)
    if((BUILD_TYPE_LOWER STREQUAL "debug") OR (BUILD_TYPE_LOWER STREQUAL "relwithdebinfo"))
        target_compile_definitions(${TARGET_NAME} PRIVATE
            -DENGINEERING
        )
    endif()
endfunction()


#! mg_target_compile_warnings : sets private warning flags for the given target
# Note: When a project needs to disable a warning, it should use a variable,
function(mg_target_compile_warnings TARGET_NAME)
    target_compile_options(${TARGET_NAME} PRIVATE
        # common flags for C and CXX for GNU and Clang compilers
        -Werror
        -Wall
        -Wextra
        -Wstrict-aliasing
        -pedantic
        -Wunreachable-code
        -Wcast-align
        -Wcast-qual
        -Winit-self
        $<$<NOT:$<BOOL:${MG_WARNING_DISABLE_MISSING_INCLUDE_DIRS}>>:-Wmissing-include-dirs>
        -Wredundant-decls
        -Wshadow
        -Wstrict-overflow=5
        -Wswitch-default
        -Wundef
        -Wno-variadic-macros
        -Wformat-nonliteral
        -Wuninitialized
        -Wformat=2
        -Werror=pointer-arith
        -Wparentheses
        -Wswitch
        -Wunused-function
        -Wno-format-zero-length
        -Wunused

        # Unsupported options in GCC < 6.0 (not sure when added)
        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
            $<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,6.0.0>:
                -Wmisleading-indentation
            >
        >

        # Unsupported options in GCC < 6.0 (not sure when added)
        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
            $<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,7.0.0>:
                #$<$<NOT:$<BOOL:${MG_WARNING_DISABLE_DUPLICATED_BRANCHES}>>:-Wduplicated-branches>
                -Wimplicit-fallthrough
            >
        >

        # CXX specific flags
        $<$<COMPILE_LANGUAGE:CXX>:
            -Wctor-dtor-privacy
            -Wsign-promo
        >

        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
            -Wlogical-op
            -Wnoexcept
            -Wstrict-null-sentinel
        >

        $<$<COMPILE_LANG_AND_ID:CXX,Clang>:
            -Wstring-conversion
            -Wno-gnu-zero-variadic-macro-arguments
        >

        # C specific flags
        $<$<COMPILE_LANGUAGE:C>:
        >

        $<$<COMPILE_LANG_AND_ID:C,GNU>:
            -Wlogical-op
        >

        $<$<COMPILE_LANG_AND_ID:C,Clang>:
        >
    )
endfunction()

#! mg_target_compile_lto : sets private LTO flags for the given target
#
# This function handles disabling of LTO when requested on a CMake scope via
# the variable MG_ENABLE_LTO
function(mg_target_compile_lto TARGET_NAME)
    set(MG_ENABLE_LTO ON CACHE BOOL "Enable/Disable building with lto")
    target_compile_options(${TARGET_NAME} PRIVATE
        # flags by build type for GNU and Clang compilers
        $<$<CONFIG:Debug>:>

        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
            $<$<NOT:$<CONFIG:Debug>>:
                $<$<BOOL:${MG_ENABLE_LTO}>:-flto>
            >
        >
    )
endfunction()

#! mg_target_compile_asan : sets private ASAN flags for the given target
#
# By default, ASAN is disabled.
# This function handles enabling of code coverage when requested on a CMake scope via
# the variable MG_ENABLE_ASAN
function(mg_target_compile_asan TARGET_NAME)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<BOOL:${MG_ENABLE_ASAN}>:-fsanitize=address -fno-omit-frame-pointer>
    )
    target_link_options(${TARGET_NAME} PRIVATE
        $<$<BOOL:${MG_ENABLE_ASAN}>:-fsanitize=address -static-libasan -rdynamic>
    )
endfunction()

#! mg_target_code_coverage : sets code coverage for the given target
#
# By default, code coverage is disabled and it will be only enabled for Debug builds.
# This function handles enabling of code coverage when requested on a CMake scope via
# the variables KAUAI_ENABLE_COVERAGE
function(mg_target_handle_code_coverage TARGET_NAME)
    if (MG_ENABLE_COVERAGE)
        target_compile_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:--coverage>
        )
        target_link_libraries(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:gcov>
        )
    endif()
endfunction()

