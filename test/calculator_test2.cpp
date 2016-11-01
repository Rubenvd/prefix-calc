#include "calculator.h"
#include "gtest/gtest.h"

TEST(DivTest, DivideBy1)
{
    EXPECT_EQ(4, divide(4,1));
    EXPECT_EQ(-22, divide(-22,1));
    EXPECT_EQ(0, divide(0,1));
}
