#include <gtest/gtest.h>
#include "../include/lab.h"
#include <cstdint>

TEST(SimpleTest1, SimpleTests) {
    ASSERT_EQ(box_capacity(32, 64, 16), 13824);
    ASSERT_EQ(box_capacity(16, 32, 64), 13824);
    ASSERT_EQ(box_capacity(64, 16, 32), 13824);
}

TEST(SimpleTest2, SimpleTests) {
    ASSERT_EQ(box_capacity(1.334, 1.334, 1.334), 1);
    ASSERT_EQ(box_capacity(1.333, 1.333, 1.333), 0);
    ASSERT_EQ(box_capacity(2.6667, 1.3334, 1.3334), 2);
}

TEST(IntOverflowTest, OverflowTests) {
    const double large_side = 3.5 * 1e6;
    const double very_large_side = 4 * 1e6;
    ASSERT_EQ(box_capacity(large_side, large_side, large_side), 18087890625000000000ull);
    ASSERT_EQ(box_capacity(very_large_side, very_large_side, very_large_side), UINT64_MAX);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}