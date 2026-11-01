#include <gtest/gtest.h>

#include "GCD.h"


TEST(positive, test01)
{
    EXPECT_EQ(gcd(9, 3), 3);
}

TEST(positive, Test02)
{
    EXPECT_EQ(6, gcd(12, 18));
}

TEST(positive, Test03)
{
    EXPECT_EQ(10, gcd(100, 10));
}

TEST(positive, Test04)
{
    EXPECT_EQ(12, gcd(24, 36));
}

TEST(positive, Test05)
{
    EXPECT_EQ(6, gcd(54, 24));
}

TEST(positive, Test06)
{
    EXPECT_EQ(6, gcd(48, 18));
}

TEST(positive, Test07)
{
    EXPECT_EQ(6, gcd(270, 192));
}

TEST(negative, Test08)
{
    EXPECT_EQ(7, gcd(-35, 14));
}

TEST(negative, Test09)
{
    EXPECT_EQ(512, gcd(1024, -512));
}

TEST(negative, Test10)
{
    EXPECT_EQ(52, gcd(-624, 364));
}

TEST(negative, Test11)
{
    EXPECT_EQ(5, gcd(-15, 25));
}

TEST(negative, Test12)
{
    EXPECT_EQ(11, gcd(33, -121));
}

TEST(doubleNegative, Test13)
{
    EXPECT_EQ(14, gcd(-42, -56));
}

TEST(doubleNegative, Test14)
{
    EXPECT_EQ(25, gcd(-75, -125));
}

TEST(doubleNegative, Test15)
{
    EXPECT_EQ(27, gcd(-81, -27));
}

TEST(doubleNegative, Test16)
{
    EXPECT_EQ(11, gcd(-99, -77));
}

TEST(zero, Test17)
{
    EXPECT_EQ(5, gcd(0, 5));
}

TEST(zero, Test18)
{
    EXPECT_EQ(12, gcd(12, 0));
}

TEST(zero, Test19)
{
    EXPECT_EQ(0, gcd(0, 0));
}

TEST(one, Test20)
{
    EXPECT_EQ(1, gcd(1, 1));
}

TEST(one, Test21)
{
    EXPECT_EQ(1, gcd(1, 100));
}

TEST(one, Test22)
{
    EXPECT_EQ(1, gcd(100, 1));
}

TEST(prime, Test23)
{
    EXPECT_EQ(1, gcd(5, 7));
}

TEST(prime, Test24)
{
    EXPECT_EQ(1, gcd(11, 13));
}

TEST(equal, Test25)
{
    EXPECT_EQ(13, gcd(13, 13));
}

TEST(equal, Test26)
{
    EXPECT_EQ(17, gcd(17, 17));
}

TEST(equal, Test27)
{
    EXPECT_EQ(23, gcd(23, 23));
}

TEST(coprime, Test28)
{
    EXPECT_EQ(1, gcd(101, 10));
}

TEST(coprime, Test29)
{
    EXPECT_EQ(1, gcd(8, 9));
}

TEST(coprime, Test30)
{
    EXPECT_EQ(1, gcd(144, 89));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
