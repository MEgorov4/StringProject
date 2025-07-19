#include "../nstring/nstring.h"
#include "gtest/gtest.h"
#include <cstring>

TEST(NStringTest, defaultCtor)
{
    str_lib::String str;
    SCOPED_TRACE("Check size of empty string");
    ASSERT_EQ(str.size(), 0);

    SCOPED_TRACE("Check capacity of empty string");
    ASSERT_EQ(str.capacity(), 15);

    SCOPED_TRACE("Check [0] to equality null-terminant");
    ASSERT_EQ(str.cstr()[0], '\0');
}

TEST(NStringTest, fromCstrCtor)
{
    const char *cstr = "abc";
    str_lib::String str = cstr;

    SCOPED_TRACE("Compare base cstr to cstr colected from str_lib::String::cstr()");
    ASSERT_TRUE(!strcmp(str.cstr(), cstr));
    ASSERT_EQ(str.size(), strlen(cstr));
    ASSERT_EQ(str.capacity(), strlen(cstr));

    const char *cstr1 =
        "l;aksdfj;laskdl;jfjs;ladkf;jklsadljfk;jlas;kdfj;lkasldj;kfklj;saldk;jf;jaslkdfasld;kfjja;slkdf";
    str_lib::String str1(cstr1);

    SCOPED_TRACE("Compare base cstr to cstr collector from str_lib::String");
    ASSERT_TRUE(!strcmp(str1.cstr(), cstr1));
    ASSERT_EQ(str1.size(), strlen(cstr1));
    ASSERT_EQ(str1.capacity(), strlen(cstr1));
}

TEST(NStringTest, copyCtor)
{
    str_lib::String original("abc");
    str_lib::String copyed(original);

    SCOPED_TRACE("Check equality of data if str_lib::String constructed by another str_lib::String");
    ASSERT_TRUE(!strcmp(original.cstr(), copyed.cstr()));

    SCOPED_TRACE("Check equality of size");
    ASSERT_EQ(original.size(), copyed.size());

    SCOPED_TRACE("Check equality of capacity");
    ASSERT_EQ(original.capacity(), copyed.capacity());

    SCOPED_TRACE("Check copyed str have diff in data-pointer value");
    ASSERT_NE(original.cstr(), copyed.cstr());
}

TEST(NStringTest, moveCtor)
{
    str_lib::String str(str_lib::String("abcdef"));

    SCOPED_TRACE("Check data");
    ASSERT_TRUE(!strcmp(str.cstr(), "abcdef"));

    SCOPED_TRACE("Check size");
    ASSERT_EQ(str.size(), 6);

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(str.capacity(), 6);

    str_lib::String original("abc");
    str_lib::String moved(std::move(original));

    SCOPED_TRACE("Check moved string data to equal 0 health");
    ASSERT_EQ(original.cstr(), nullptr);

    SCOPED_TRACE("Check data");
    ASSERT_TRUE(!strcmp(moved.cstr(), "abc"));

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(moved.size(), 3);

    SCOPED_TRACE("Check capacity");
    ASSERT_EQ(moved.capacity(), 3);
}

TEST(NStringTest, assignFromCstr)
{
    str_lib::String str;
    str = "hello";

    SCOPED_TRACE("Check content after assignment from const char*");
    ASSERT_TRUE(!strcmp(str.cstr(), "hello"));

    SCOPED_TRACE("Check size after assignment");
    ASSERT_EQ(str.size(), 5);

    SCOPED_TRACE("Check capacity after assignment");
    ASSERT_EQ(str.capacity(), 5);
}

TEST(NStringTest, copyAssignment)
{
    str_lib::String original("world");
    str_lib::String copyed;
    copyed = original;

    SCOPED_TRACE("Check content equality after copy assignment");
    ASSERT_TRUE(!strcmp(original.cstr(), copyed.cstr()));

    SCOPED_TRACE("Check size equality");
    ASSERT_EQ(original.size(), copyed.size());

    SCOPED_TRACE("Check capacity equality");
    ASSERT_EQ(original.capacity(), copyed.capacity());

    SCOPED_TRACE("Ensure deep copy (different buffers)");
    ASSERT_NE(original.cstr(), copyed.cstr());
}

TEST(NStringTest, moveAssignment)
{
    str_lib::String original("data");
    str_lib::String moved;
    moved = std::move(original);

    SCOPED_TRACE("Check moved-from string is null");
    ASSERT_EQ(original.cstr(), nullptr);

    SCOPED_TRACE("Check moved-to string content");
    ASSERT_TRUE(!strcmp(moved.cstr(), "data"));

    SCOPED_TRACE("Check moved-to string size");
    ASSERT_EQ(moved.size(), 4);

    SCOPED_TRACE("Check moved-to string capacity");
    ASSERT_EQ(moved.capacity(), 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
