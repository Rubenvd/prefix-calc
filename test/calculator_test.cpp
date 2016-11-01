#include "calculator.h"
#include "gtest/gtest.h"

TEST(DividerTest, DivideByZero)
{
    EXPECT_EQ(0, divide(1,0));
    EXPECT_EQ(0, divide(-1,0));
    EXPECT_EQ(0, divide(0,0));
}

TEST(DividerTest, DivideNegative)
{
    EXPECT_EQ(3, divide(-9, -3));
    EXPECT_EQ(-3, divide(9, -3));
    EXPECT_EQ(-3, divide(-9, 3));
}
