#ifndef NSTRING_GETTERS_GT_HPP
#define NSTRING_GETTERS_GT_HPP

#include <gtest/gtest.h>
#include "nstring.h"

TEST(NStringEmpty, defaultConstructedIsEmpty)
{
	nstring::String s;
	ASSERT_TRUE(s.empty());
	ASSERT_EQ(s.size(), 0);
}

TEST(NStringEmpty, nonEmptyString)
{
	nstring::String s("text");
	ASSERT_FALSE(s.empty());
	ASSERT_GT(s.size(), 0);
}

TEST(NStringEmpty, afterClear)
{
	nstring::String s("data");
	s.clear();
	ASSERT_TRUE(s.empty());
	ASSERT_EQ(s.size(), 0);
	ASSERT_EQ(s.cstr()[0], '\0');
}

TEST(NStringEmpty, afterResizeToZero)
{
	nstring::String s("abc");
	s.resize(0);
	ASSERT_TRUE(s.empty());
	ASSERT_EQ(s.size(), 0);
}

TEST(NStringGetters, cstrReturnsNullTerminatedData)
{
	nstring::String s("hello");
	ASSERT_STREQ(s.cstr(), "hello");
	ASSERT_EQ(s.cstr()[s.size()], '\0');
}

TEST(NStringGetters, sizeReturnsCorrectLength)
{
	nstring::String s("123456");
	ASSERT_EQ(s.size(), 6);
}

TEST(NStringGetters, capacityReturnsAtLeastBaseOrSize)
{
	nstring::String s("abc");
	ASSERT_GE(s.capacity(), s.size());
	ASSERT_GE(s.capacity(), nstring::String::BASE_CAPACITY);
}

#endif  // !NSTRING_GETTERS_GT_HPP
