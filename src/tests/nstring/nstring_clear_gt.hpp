#ifndef NSTRING_CLEAR_GT_HPP
#define NSTRING_CLEAR_GT_HPP

#include <gtest/gtest.h>

#include "nstring.h"

TEST(NStringClear, clearsStringCorrectly)
{
	nstring::String str = "clear me";

	SCOPED_TRACE("Clear should reset size to 0");
	str.clear();
	ASSERT_EQ(str.size(), 0);

	SCOPED_TRACE("Clear should preserve capacity");
	ASSERT_GE(str.capacity(), nstring::String::BASE_CAPACITY);

	SCOPED_TRACE("Clear should set first char to null terminator");
	ASSERT_EQ(str.cstr()[0], '\0');

	SCOPED_TRACE("empty() should return true after clear()");
	ASSERT_TRUE(str.empty());
}


#endif  // !NSTRING_CLEAR_GT_HPP
