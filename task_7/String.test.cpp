#include "String.hpp"
#include <gtest/gtest.h>

TEST(StringTest, DefaultConstructor)
{
    const String s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_STREQ(s.c_str(), "");
}

TEST(StringTest, ParameterizedConstructor)
{
    const String s("Parameter");
    EXPECT_EQ(s.size(), 9);
    EXPECT_STREQ(s.c_str(), "Parameter");
}

TEST(StringTest, CopyConstructor)
{
    const String s1("Copy");
    const String s2(s1);
    EXPECT_EQ(s2.size(), 4);
    EXPECT_STREQ(s2.c_str(), "Copy");
}

TEST(StringTest, CopyAssignment)
{
    const String s1("CopyAssign");
    String s2;
    s2 = s1;
    EXPECT_EQ(s2.size(), 10);
    EXPECT_STREQ(s2.c_str(), "CopyAssign");
}

TEST(StringTest, MoveConstructor)
{
    String s1("Move");
    const String s2(std::move(s1));
    EXPECT_EQ(s2.size(), 4);
    EXPECT_STREQ(s2.c_str(), "Move");
}

TEST(StringTest, MoveAssignment)
{
    String s1("MoveAssign");
    String s2;
    s2 = std::move(s1);
    EXPECT_EQ(s2.size(), 10);
    EXPECT_STREQ(s2.c_str(), "MoveAssign");
}

TEST(StringTest, AtMethod)
{
    String s("Method");
    EXPECT_EQ(s.at(0), 'M');
    EXPECT_EQ(s.at(5), 'd');
    EXPECT_THROW(s.at(6), std::out_of_range);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
