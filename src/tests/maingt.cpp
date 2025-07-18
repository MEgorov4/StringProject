#include "../nstring/nstring.h"
#include "gtest/gtest.h"

TEST(NStringTest, emptyString)
{
    str_lib::String str;
    SCOPED_TRACE("Check size of empty string");
    ASSERT_EQ(str.size(), 0);

    SCOPED_TRACE("Check capacity of empty string");
    ASSERT_EQ(str.capacity(), 15);

    SCOPED_TRACE("Check [0] to equality null-terminant");
    ASSERT_EQ(str.cstr()[0], '\0');
}

TEST(NStringTest, constructFromCstr)
{
    const char *cstr = "abc";
    str_lib::String str = cstr;

    SCOPED_TRACE("Compare base cstr to cstr colected from str_lib::String::cstr()");
    ASSERT_TRUE(!strcmp(str.cstr(), cstr));
}

TEST(NStringTest, constructFromAnotherString)
{
    str_lib::String str1("abc");
    str_lib::String str2(str1);

    SCOPED_TRACE("Check equality of data if str_lib::String constructed by another str_lib::String");
    ASSERT_TRUE(!strcmp(str1.cstr(), str2.cstr()));

    SCOPED_TRACE("Check equality of size");
    ASSERT_EQ(str1.size(), str2.size());

    SCOPED_TRACE("Check equality of capacity");
    ASSERT_EQ(str1.capacity(), str2.capacity());

    SCOPED_TRACE("Check copyed str have diff in data-pointer value");
    ASSERT_NE(str1.cstr(), str2.cstr());
}

TEST(NStringTest, movConstructFromAnotherString)
{
    str_lib::String str1(str_lib::String("abcdef"));

    SCOPED_TRACE("Check data");
    ASSERT_TRUE(!strcmp(str1.cstr(), "abcdef"));

    SCOPED_TRACE("Check size");
    ASSERT_EQ(str1.size(), 6);

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(str1.capacity(), 6);

    str_lib::String str2("abc");
    str_lib::String str3(std::move(str2));

    SCOPED_TRACE("Check moved string data to equal 0 health");
    ASSERT_EQ(str2.cstr(), nullptr);

    SCOPED_TRACE("Check data");
    ASSERT_TRUE(!strcmp(str3.cstr(), "abc"));

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(str3.size(), 3);

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(str3.capacity(), 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
