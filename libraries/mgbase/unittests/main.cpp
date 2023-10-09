/**
 * \file     main.cpp
 * \brief    Custom main for GTest, allows local init and exit before invoking tests
 */

// ==== System includes, namespaces, local includes ===========================================================
#include "gtest/gtest.h"

int main(int argc, char** argv)
{
    // Any special initialisation goes here
    // Posutils needed to ensure the pu_timer_xxx stuff is initialised for the "Micron" tests

    // GTEST
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    // Any special cleanup goes here

    // done
    return result;
}
