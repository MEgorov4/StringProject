#ifndef NSTRING_CTORS_GT_HPP
#define NSTRING_CTORS_GT_HPP

#include <stdexcept>
#include <gtest/gtest.h>

#include "nstring.h"

TEST(NStringCtors, defaultCtor)
{
	nstring::String str;
	SCOPED_TRACE("Check size of empty string");
	ASSERT_EQ(str.size(), 0);

	SCOPED_TRACE("Check capacity of empty string");
	ASSERT_EQ(str.capacity(), nstring::String::BASE_CAPACITY);

	SCOPED_TRACE("Check [0] to equality null-terminant");
	ASSERT_EQ(str.cstr()[0], '\0');
}

TEST(NStringCtors, fillCharsCtor)
{
	nstring::String zero(0, '\0');
	SCOPED_TRACE("Check size of empty string");
	ASSERT_EQ(zero.size(), 0);

	SCOPED_TRACE("Check capacity of empty string");
	ASSERT_EQ(zero.capacity(), 15);

	SCOPED_TRACE("Check str.cstr == base char");
	ASSERT_TRUE(strcmp(zero.cstr(), "\0") == 0);

	nstring::String str(10, 'x');
	const char* valid = "xxxxxxxxxx";

	SCOPED_TRACE("Check size of filled string");
	ASSERT_EQ(str.size(), 10);

	SCOPED_TRACE("Check capacity of filled string");
	ASSERT_EQ(str.capacity(), 15);

	SCOPED_TRACE("Check str.cstr == base char");
	ASSERT_TRUE(strcmp(str.cstr(), valid) == 0);
}
TEST(NStringCtors, fromCstrCtor)
{
	const char* cstr = "abc";
	nstring::String str = cstr;

	SCOPED_TRACE("Compare base cstr to cstr colected from nstring::String::cstr()");
	ASSERT_TRUE(!strcmp(str.cstr(), cstr));
	ASSERT_EQ(str.size(), strlen(cstr));
	ASSERT_EQ(str.capacity(), nstring::String::BASE_CAPACITY);

	const char* bigCstr =
	    "l;aksdfj;laskdl;jfjs;ladkf;jklsadljfk;jlas;kdfj;"
	    "lkasldj;kfklj;saldk;jf;jaslkdfasld;kfjja;slkdf";
	nstring::String bigStr(bigCstr);

	SCOPED_TRACE("Compare base cstr to cstr collected from nstring::String");
	ASSERT_TRUE(!strcmp(bigStr.cstr(), bigCstr));
	ASSERT_EQ(bigStr.size(), strlen(bigCstr));
	ASSERT_EQ(bigStr.capacity(), strlen(bigCstr));
}

TEST(NStringCtors, fromCstrCtorNullThrow)
{
	ASSERT_THROW(nstring::String str(nullptr), std::invalid_argument);
}

TEST(NStringCtors, copyCtor)
{
	nstring::String original("abc");
	nstring::String copyed(original);

	SCOPED_TRACE(
	    "Check equality of data if nstring::String constructed by "
	    "another nstring::String");
	ASSERT_TRUE(!strcmp(original.cstr(), copyed.cstr()));

	SCOPED_TRACE("Check equality of size");
	ASSERT_EQ(original.size(), copyed.size());

	SCOPED_TRACE("Check equality of capacity");
	ASSERT_EQ(original.capacity(), copyed.capacity());

	SCOPED_TRACE("Check copyed str have diff in data-pointer value");
	ASSERT_NE(original.cstr(), copyed.cstr());
}

TEST(NStringCtors, moveCtor)
{
	nstring::String str(nstring::String("abcdef"));

	SCOPED_TRACE("Check data");
	ASSERT_TRUE(!strcmp(str.cstr(), "abcdef"));

	SCOPED_TRACE("Check size");
	ASSERT_EQ(str.size(), 6);

	SCOPED_TRACE("Check capacity");
	ASSERT_EQ(str.capacity(), nstring::String::BASE_CAPACITY);

	nstring::String original("abc");
	nstring::String moved(std::move(original));

	SCOPED_TRACE("Check moved string data to equal 0 health");
	ASSERT_EQ(original.cstr(), nullptr);

	SCOPED_TRACE("Check data");
	ASSERT_TRUE(!strcmp(moved.cstr(), "abc"));

	SCOPED_TRACE("Check capacity");
	ASSERT_EQ(moved.size(), 3);

	SCOPED_TRACE("Check capacity");
	ASSERT_EQ(moved.capacity(), nstring::String::BASE_CAPACITY);
}

#endif
