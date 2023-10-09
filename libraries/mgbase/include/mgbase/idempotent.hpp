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
#ifndef MG_IDEMPOTENT_HPP
#define MG_IDEMPOTENT_HPP

/**
 * \file     idempotent.hpp
 * \author   mg4news
 * \date     2023-09-20
 */

#include "mgbase/base.hpp"

#include <atomic>

namespace mgbase
{
    
/*
 * \brief
 * Utility class to manage idempotent initialisation and exit, i.e.
 * - where init and exit are simply logical steps, NOT necessarily linked to construction and destruction.
 *   For example, they could be tied to foreground and background management
 * - idempotent initialisation guarantees that at time of initialisation if multiple entities trigger the call, it:
 *   - executes only once
 *   - the transition to "initialised" is atomic
 * - idempotent exit guarantees that at time of initialisation if multiple entities trigger the call, it:
 *   - executes only once
 *   - the transition to "un-initialised" is atomic
 * Inheritance CANNOT be used, static functions cannot be virtual
 */
class Idempotent final
{
    MG_CLASS_NOT_COPYABLE(Idempotent);
    MG_CLASS_NOT_MOVABLE(Idempotent);

public:
    Idempotent() = default;
    ~Idempotent() = default;

    /**
     * \brief Check if is initialised
     * \return true if initialised, elase false 
     */
    bool isInit() { return (mIsInit != 0); }

    /**
     * \brief Initialise an idempotent instance
     * \return true on success, if already initialised then false 
     */
    bool init();

    /**
     * \brief Exit (uninitialise) an idempotent instance
     * \return true on success, false if the instance is already uninitialised 
     */
    bool exit();

private:
    std::atomic<int> mIsInit { 0 };
};

} // namespace mg4news

#endif /* MG_IDEMPOTENT_HPP */
