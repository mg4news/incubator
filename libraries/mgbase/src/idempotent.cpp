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

/**
 * \file     idempotent.cpp
 * \author   mg4news
 * \date     2023-09-20
 *
 * \brief
 * Idempotent initialisation utility class.
 */

#include "mgbase/idempotent.hpp"

using namespace mgbase;

// Anonymous name space
namespace
{

} // anonymous namespace

// ==========================================================================================================
// Idempotent methods
// ==========================================================================================================

// Can be called multiple times
// Will only return true on the atomic transition to "isInit() == true"
bool Idempotent::init()
{
    int expectedValue = 0;
    int desiredValue = 1;
    return (mIsInit.compare_exchange_strong(expectedValue, desiredValue));
}
// Idempotent::init

// Can be called multiple times
// Will only return true on the atomic transition to "isInit() != true"
bool Idempotent::exit()
{
    int expectedValue = 1;
    int desiredValue = 0;
    return (mIsInit.compare_exchange_strong(expectedValue, desiredValue));
}
// Idempotent::init