
#include <gtest/gtest.h>
#include "math.h"

TEST(MathTest, Add) {
    EXPECT_EQ(add(2, 3), 5);       // 2 + 3 = 5
    EXPECT_EQ(add(-1, 1), 0);      // -1 + 1 = 0
}

TEST(MathTest, Subtract) {
    EXPECT_EQ(subtract(5, 3), 2);   // 5 - 3 = 2
    EXPECT_EQ(subtract(0, 1), -1);  // 0 - 1 = -1
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
