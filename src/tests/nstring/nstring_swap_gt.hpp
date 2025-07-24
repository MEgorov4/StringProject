#ifndef NSTRING_SWAP_GT_HPP
#define NSTRING_SWAP_GT_HPP

#include <gtest/gtest.h>
#include "nstring.h"

TEST(NStringSwap, memberSwapSwapsContents)
{
	nstring::String a = "hello";
	nstring::String b = "world";

	a.swap(b);

	SCOPED_TRACE("Swap should exchange content");
	ASSERT_STREQ(a.cstr(), "world");
	ASSERT_STREQ(b.cstr(), "hello");

	SCOPED_TRACE("Size and capacity should also be swapped");
	ASSERT_EQ(a.size(), 5);
	ASSERT_EQ(b.size(), 5);
}

TEST(NStringSwap, nonMemberSwapSwapsContents)
{
	nstring::String a = "abc";
	nstring::String b = "xyz";

	swap(a, b);

	SCOPED_TRACE("Non-member swap should work the same");
	ASSERT_STREQ(a.cstr(), "xyz");
	ASSERT_STREQ(b.cstr(), "abc");
	ASSERT_EQ(a.size(), 3);
	ASSERT_EQ(b.size(), 3);
}

#endif  // !NSTRING_SWAP_GT_HPP
