//=============================================================================
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any means.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// This is a simplified version of UNLICENSE. For more information,
// please refer to <http://unlicense.org/>
//=============================================================================
#ifndef MG_BASE_HPP
#define MG_BASE_HPP

/**
 * \file     base.hpp
 * \author   mg4news
 * \date     2023-09-20
 */

#include <stdlib.h>
#include <stdint.h>
#include <string>

// Enforce GCC 7 or better - if GCC is used
#if defined(__GNUC__) || defined(__GNUG__)
    #if (__GNUC__ < 7)
        #error "Require a minimum of GCC 7"
    #endif    
#endif

// Macro to declare a class non-copyable.
#define MG_CLASS_NOT_COPYABLE(name) \
    name(name const&) = delete;     \
    name& operator=(name const&) = delete

// Macro to declare a class non-movable.
#define MG_CLASS_NOT_MOVABLE(name) \
    name(name&&) = delete;         \
    name& operator=(name&&) = delete

// Macro to declare a parameter as unused.
#define MG_UNUSED(parameter) (void)parameter

// Macro to declare a function or method result as unused.
#define MG_UNUSED_RESULT(expression) \
    do {                             \
        (void)expression;            \
    }                                \
    while (false)

// Macro to declare an intended case fallthrough.
#if defined(__clang__)
    #define MG_FALLTHROUGH [[clang::fallthrough]]
#elif defined(__GNUC__) || defined(__GNUG__)
    #define MG_FALLTHROUGH __attribute__((fallthrough))
#else
    #error "Unsupported compiler."
#endif

#endif // MG_BASE_HPP

/**
 * @brief Version utility functions 
 */
namespace mgbase {
    std::string version();
    int         version_major();
    int         version_minor();
    int         version_patch();
}
