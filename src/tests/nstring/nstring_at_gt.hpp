#ifndef NSTRING_AT_GT_HPP
#define NSTRING_AT_GT_HPP

#include <gtest/gtest.h>

#include "nstring.h"


TEST(NStringAtMethod, validIndexAccess)
{
	nstring::String str("hello");

	SCOPED_TRACE("Access character at valid index");
	ASSERT_EQ(str.at(0), 'h');
	ASSERT_EQ(str.at(4), 'o');

	str.at(1) = 'a';
	ASSERT_EQ(str.at(1), 'a');
}

TEST(NStringAtMethod, constAccess)
{
	const nstring::String str("const");

	SCOPED_TRACE("Access const String");
	ASSERT_EQ(str.at(0), 'c');
	ASSERT_EQ(str.at(4), 't');
}

TEST(NStringAtMethod, outOfRangeAccessThrows)
{
	nstring::String str("abc");

	SCOPED_TRACE("Expect out_of_range for invalid index");
	EXPECT_THROW(str.at(3), std::out_of_range);
	EXPECT_THROW(str.at(100), std::out_of_range);
}

TEST(NStringAtMethod, outOfRangeAccessThrowsConst)
{
	const nstring::String str("xyz");

	SCOPED_TRACE("Expect out_of_range for const invalid index");
	EXPECT_THROW(str.at(3), std::out_of_range);
	EXPECT_THROW(str.at(999), std::out_of_range);
}

#endif  // !NSTRING_AT_GT_HPP
