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
#ifndef MG_ASSERT_HPP
#define MG_ASSERT_HPP

/**
 * \file     assert.hpp
 * \author   mg4news
 * \date     2023-09-20
 * 
 * \brief 
 * Some assert utilities. Using GSL for DbC (Design by Contract)
 */

#include <stdio.h>
#include <exception>

namespace mgbase::assert
{
[[noreturn]] void terminate_on_assertion(const char* expression, const char* file, int line);
void warn_on_assertion(const char* expression, const char* file, int line);
}


namespace mgbase
{

// Used in the DbC macros
#define MG_CONCAT_IMPL(a, b) a##b
#define MG_CONCAT(a, b) MG_CONCAT_IMPL(a, b)


// Terminate the program
#define MG_TERMINATE() std::terminate()

// Assert with useful message
// Note, there are cases where you need the assertion to be tested AND reported, but without terminating, and without completely
// disabling termination for everything. the WARN macros achieve that.
#ifndef NDEBUG
    #define MG_ASSERT(expression, message)                                                             \
        do {                                                                                           \
            if (!(expression)) {                                                                       \
                ::mgbase::assert::terminate_on_assertion(message ":" #expression, __FILE__, __LINE__); \
            }                                                                                          \
        }                                                                                              \
        while (false)

    #define MG_WARN(expression)                                                       \
        do {                                                                          \
            if (!(expression)) {                                                      \
                ::mgbase::assert::warn_on_assertion(#expression, __FILE__, __LINE__); \
            }                                                                         \
        }                                                                             \
        while (false)

    #define MG_WARN_MSG(expression, message)                                                      \
        do {                                                                                      \
            if (!(expression)) {                                                                  \
                ::mgbase::assert::warn_on_assertion(message ":" #expression, __FILE__, __LINE__); \
            }                                                                                     \
        }                                                                                         \
        while (false)
#else
    #define MG_ASSERT(expression) ((void)0)
    #define MG_WARN(expression) ((void)0)
    #define MG_WARN_MSG(expression, message) ((void)0)
#endif // NDEBUG

//
// Design by contract require macro.
//
// Function/method preconditions express the requirements that callers must
// satisfy whenever the function is called.  Preconditions are specified by
// the K_REQUIRE() macro. When the precondition expression evaluates to false,
// the macro aborts in debug builds. In release builds the macro returns
// from the function with the specified result value when the expression
// evaluates to false.
//
#ifndef NDEBUG
    #define K_REQUIRE(expression, result)                                                             \
        do {                                                                                          \
            if (!(expression)) {                                                                      \
                ::mgbase::assert::terminate_on_failed_precondition(#expression, __FILE__, __LINE__); \
                return result;                                                                        \
            }                                                                                         \
        }                                                                                             \
        while (false)
#else
    #define K_REQUIRE(expression, result) \
        do {                              \
            if (!(expression)) {          \
                return result;            \
            }                             \
        }                                 \
        while (false)
#endif

}

#endif // MG_ASSERT_HPP
