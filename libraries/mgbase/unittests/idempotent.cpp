// ==========================================================================================================
// THIS SOFTWARE IS CONFIDENTIAL AND PROPRIETARY PROPERTY OF ACTIVEVIDEO NETWORKS LLC OR ITS AFFILIATES.
//
// Copyright (c) 2021 ActiveVideo Networks LLC. All rights reserved.
//
// ActiveVideo, AppCloud, and CloudTV are trademarks or registered trademarks of ActiveVideo.
// All other trademarks are the property of their respective owners.
//
// This software and the accompanying documentation are the confidential and proprietary products of
// ActiveVideo Networks LLC or its affiliates, the use of which is governed by the terms and conditions
// of a separate written agreement entered into by you with ActiveVideo Networks LLC or its affiliates.
// The software and accompanying documentation may be covered by one or more U.S. or international patents
// and patent applications in addition to being protected by applicable trade secret and copyright laws.
// U.S. Patents are listed at http://www.activevideo.com/patents
// THE SOFTWARE MAY NOT BE COPIED, COMPILED, DECOMPILED, DISTRIBUTED, MODIFIED, OR TRANSFERRED WITHOUT THE
// EXPRESS PRIOR WRITTEN PERMISSION OF ACTIVEVIDEO NETWORKS LLC AND ITS LICENSORS, IF ANY.
//
// ActiveVideo Networks LLC
// 333 W. San Carlos St. Suite 900
// San Jose, CA 95110
// United States
// ==========================================================================================================

/**
 * \file     idempotent.cpp
 * \brief    Idempotent object unit tests
 */

// ==== System includes, namespaces, local includes ===========================================================
#include "gtest/gtest.h"
#include "mgbase/idempotent.hpp"

using namespace mgbase;

TEST(Idempotent, Basic)
{
    Idempotent idempotent {};

    // It should start uninitialised
    ASSERT_FALSE(idempotent.isInit());

    // First init should return true
    ASSERT_TRUE(idempotent.init());

    // Must now be initialised
    ASSERT_TRUE(idempotent.isInit());

    // Successive inits should return false
    int i = 0;
    while (i < 10) {
        ASSERT_FALSE(idempotent.init());
        i++;
    }

    // Must STILL be initialised
    ASSERT_TRUE(idempotent.isInit());

    // First exit should return true
    ASSERT_TRUE(idempotent.exit());

    // Must now NOT be initialised
    ASSERT_FALSE(idempotent.isInit());

    // Successive exits should return false
    while (i < 10) {
        ASSERT_FALSE(idempotent.exit());
        i++;
    }

    // Must STILL NOT be initialised
    ASSERT_FALSE(idempotent.isInit());
}
