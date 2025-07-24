#ifndef NSTRING_RESERVE_GT_HPP
#define NSTRING_RESERVE_GT_HPP

#include <gtest/gtest.h>

#include "nstring.h"

TEST(NStringReserve, reserveDoesNothingWhenCapacityIsEnough)
{
	nstring::String str = "abc";
	size_t oldCap = str.capacity();
	str.reserve(oldCap - 1);

	SCOPED_TRACE("Capacity should remain unchanged when reserving less");
	ASSERT_EQ(str.capacity(), oldCap);
	ASSERT_TRUE(!strcmp(str.cstr(), "abc"));
}

TEST(NStringReserve, reserveZeroDoesNothing)
{
	nstring::String str = "abc";
	size_t oldCap = str.capacity();
	str.reserve(0);

	SCOPED_TRACE("Reserving 0 must not affect capacity or data");
	ASSERT_EQ(str.capacity(), oldCap);
	ASSERT_TRUE(!strcmp(str.cstr(), "abc"));
}

TEST(NStringReserve, reserveIncreasesCapacity)
{
	nstring::String str = "abc";
	size_t oldCap = str.capacity();
	str.reserve(oldCap + 10);

	SCOPED_TRACE("Capacity should increase");
	ASSERT_GE(str.capacity(), oldCap + 10);
	ASSERT_TRUE(!strcmp(str.cstr(), "abc"));
}

TEST(NStringReserve, reservePreservesData)
{
	nstring::String str = "hello world";
	const char* oldData = str.cstr();
	str.reserve(str.capacity() + 20);

	SCOPED_TRACE("Content must stay the same after reserve");
	ASSERT_TRUE(!strcmp(str.cstr(), "hello world"));
	ASSERT_NE(str.cstr(), oldData);
}

TEST(NStringReserve, reserveThrowsOnOverflow)
{
	nstring::String str;

	SCOPED_TRACE("Expect std::length_error when trying to reserve SIZE_MAX");
	ASSERT_THROW(str.reserve(SIZE_MAX), std::length_error);
}

#endif  // !NSTRING_RESERVE_GT_HPP
