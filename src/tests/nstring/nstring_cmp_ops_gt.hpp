#ifndef NSTRING_CMP_OPS_GT_HPP
#define NSTRING_CMP_OPS_GT_HPP

#include <gtest/gtest.h>

#include "nstring.h"

using nstring::String;

TEST(NStringCompareOps, equalityOperators)
{
	String a = "hello";
	String b = "hello";
	String c = "world";

	SCOPED_TRACE("Check equality and inequality between Strings");
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
	ASSERT_TRUE(a != c);

	const char* raw = "hello";
	ASSERT_TRUE(a == raw);
	ASSERT_TRUE(raw == a);
	ASSERT_FALSE(a != raw);
	ASSERT_FALSE(raw != a);
}

TEST(NStringCompareOps, lessThanOperators)
{
	String a = "abc";
	String b = "bcd";

	SCOPED_TRACE("Check < operator");
	ASSERT_TRUE(a < b);
	ASSERT_FALSE(b < a);

	const char* raw = "zzz";
	ASSERT_TRUE(a < raw);
	ASSERT_TRUE(raw > a);
}

TEST(NStringCompareOps, lessThanOrEqualOperators)
{
	String a = "aaa";
	String b = "bbb";
	String c = "aaa";

	SCOPED_TRACE("Check <= operator");
	ASSERT_TRUE(a <= b);
	ASSERT_TRUE(a <= c);
	ASSERT_FALSE(b <= a);

	const char* raw = "zzz";
	ASSERT_TRUE(a <= raw);
	ASSERT_FALSE(raw <= a);
}

TEST(NStringCompareOps, greaterThanOperators)
{
	String a = "xyz";
	String b = "uvw";

	SCOPED_TRACE("Check > operator");
	ASSERT_TRUE(a > b);
	ASSERT_FALSE(b > a);

	const char* raw = "abc";
	ASSERT_TRUE(a > raw);
	ASSERT_FALSE(raw > a);
}

TEST(NStringCompareOps, greaterThanOrEqualOperators)
{
	String a = "same";
	String b = "same";
	String c = "diff";

	SCOPED_TRACE("Check >= operator");
	ASSERT_TRUE(a >= b);
	ASSERT_TRUE(a >= c);
	ASSERT_FALSE(c >= a);

	const char* raw = "aaa";
	ASSERT_TRUE(a >= raw);
	ASSERT_FALSE(raw >= a);
}

#endif  // !NSTRING_CMP_OPS_GT_HPP
