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
#ifndef MG_SEM_HPP
#define MG_SEM_HPP

/**
 * \file     sem.hpp
 * \author   mg4news
 * \date     2023-09-20
 */

#include "mgbase/base.hpp"

#include <semaphore.h>

namespace mgbase
{
/*
 * @brief A wrapper class for the POSIX semaphore.
 *
 * ## Description
 * C++ does not add semaphores until C++20. Because I am opinionated, I think they did a poor job when adding them
 * The POSIX usage is completely adequate for all use case. This class adds a C++ friendly wrapper that helps people 
 * overcome the massive mental and emotional challenges of working directly with POSIX primitives.
 *
 * ## Why use a semaphore
 * A mutex is a locking mechanism. A semaphore is a signalling mechanism. These are very different intents.
 * It is possible to contrive a semaphore to look like a mutex and vice versa, but it makes more sense
 * to each primitive for its intended functionality
 *
 * ## Single process
 * This implementation only covers the single process use case.
 *
 * @note
 * The C++20 terminology is logically incorrect. It describes a semaphore to sound like a mutex (i.e. acquire, release).
 * This is semantically wrong. A semaphore is not a mutual exculsion mechanism, it is a synchronisation primitve. 
 * You wait on a semaphore. Once the synchronisation event has passed, the code continues to execute. Unlike a mutex 
 * there is no "owning" thread. Any thread can signal/post a semaphore. The interface provides two sets of signatures
 * - a set of methods using the the correct terminology
 * - a set of methods using C++20 terminology (purly for compatibility, doesn't mean I like it)
 * .
 * Does not distinguish between a binary semaphore and a counting semaphore. In reality a binary semaphore is simply a usage
 * of a counting semaphore with an initial count of 0, there is no difference in the underlying implementation in POSIX.
 */
class Sem final
{
    MG_CLASS_NOT_COPYABLE(Sem);
    MG_CLASS_NOT_MOVABLE(Sem);

    /**
     * @brief Default constructor
     *
     * ## Description
     * This should be the normal use case. The semaphore starts with a zero count. The first wait (aka "acquire")
     * will pend till someone signals ()
     */
    Sem() {sem_init(&mSem, 0, 0);}

    /**
     * @brief Parameterised constructor
     * @param count the count the semaphore is initialised with
     *
     * ## Description
     * Only use if you have a specialised synchronisation use case
     */
    Sem(int count = 0) {sem_init(&mSem, 0, count);}

    /**
     * @brief Destructor
     */
    ~Sem() {sem_destroy(&mSem);}

    /**
     * @brief Wait (pend) until the semaphore is signalled
     */
    void wait() {sem_wait(&mSem);}

    /**
     * @brief Try wait on the semaphore
     * @return true if the wait succeeded, else false
     */
    bool trywait() {return (0 == sem_trywait(&mSem));}

    /**
     * @brief Post to (signal) the semaphore
     */
    void post() {sem_post(&mSem);}

    //=============================================================================================
    // C++20 compatibility section
    // Logically wrong, but matches the standard
    //=============================================================================================

    /**
     * @brief Wait for the semaphore to be signalled
     */
    void acquire() {wait();}

    /**
     * @brief Try wait on the semaphore
     */
    bool try_acquire() {return trywait();}

    /**
     * @brief Post to (signal) the semaphore
     */
    void release() {post();}

private:
    sem_t mSem;

};

} // namespace mg4news

#endif // MG_SEM_HPP