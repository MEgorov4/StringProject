#ifndef NSTRING_RESIZE_GT_HPP
#define NSTRING_RESIZE_GT_HPP
#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringResize, resizeShrink )
{
	str_lib::String str = "abcdef";
	str.resize( 3 );

	SCOPED_TRACE( "Resize to smaller size (shrink)" );
	ASSERT_EQ( str.size(), 3 );
	ASSERT_TRUE( !strcmp( str.cstr(), "abc" ) );
}

TEST( NStringResize, resizeGrowDefaultChar )
{
	str_lib::String str = "abc";
	str.resize( 6 );

	SCOPED_TRACE( "Resize to larger size with default char ('\\0')" );
	ASSERT_EQ( str.size(), 6 );
	ASSERT_EQ( str.cstr()[0], 'a' );
	ASSERT_EQ( str.cstr()[1], 'b' );
	ASSERT_EQ( str.cstr()[2], 'c' );
	ASSERT_EQ( str.cstr()[3], '\0' );
	ASSERT_EQ( str.cstr()[4], '\0' );
	ASSERT_EQ( str.cstr()[5], '\0' );
}

TEST( NStringResize, resizeGrowCustomChar )
{
	str_lib::String str = "xy";
	str.resize( 5, 'z' );

	SCOPED_TRACE( "Resize to larger size with custom char" );
	ASSERT_EQ( str.size(), 5 );
	ASSERT_EQ( str[0], 'x' );
	ASSERT_EQ( str[1], 'y' );
	ASSERT_EQ( str[2], 'z' );
	ASSERT_EQ( str[3], 'z' );
	ASSERT_EQ( str[4], 'z' );
	ASSERT_TRUE( !memcmp( str.cstr(), "xyzzz", 5 ) );
}

TEST( NStringResize, resizeToZero )
{
	str_lib::String str = "abc";
	str.resize( 0 );

	SCOPED_TRACE( "Resize to zero length" );
	ASSERT_EQ( str.size(), 0 );
	ASSERT_EQ( str.cstr()[0], '\0' );
}

TEST( NStringResize, resizeNoOp )
{
	str_lib::String str = "test";
	str.resize( 4 );

	SCOPED_TRACE( "Resize to same size (no-op)" );
	ASSERT_EQ( str.size(), 4 );
	ASSERT_TRUE( !strcmp( str.cstr(), "test" ) );
}

TEST( NStringResize, resizeGrowWithinCapacity )
{
	str_lib::String str = "abc";
	str.reserve( 10 );
	str.resize( 6, 'x' );

	SCOPED_TRACE( "Resize grow that fits within reserved capacity" );
	ASSERT_EQ( str.size(), 6 );
	ASSERT_EQ( str[0], 'a' );
	ASSERT_EQ( str[1], 'b' );
	ASSERT_EQ( str[2], 'c' );
	ASSERT_EQ( str[3], 'x' );
	ASSERT_EQ( str[4], 'x' );
	ASSERT_EQ( str[5], 'x' );
	ASSERT_TRUE( !memcmp( str.cstr(), "abcxxx", 6 ) );
}

TEST( NStringResize, resizeGrowTriggersRealloc )
{
	str_lib::String str          = "abc";
	const size_t    old_capacity = str.capacity();
	str.resize( old_capacity + 10, 'y' );

	SCOPED_TRACE( "Resize grow that triggers reallocation" );
	ASSERT_GE( str.capacity(), old_capacity + 10 );
	ASSERT_EQ( str.size(), old_capacity + 10 );
	ASSERT_EQ( str[0], 'a' );
	ASSERT_EQ( str[1], 'b' );
	ASSERT_EQ( str[2], 'c' );
	for( size_t i = 3; i < str.size(); ++i )
	{
		ASSERT_EQ( str[i], 'y' );
	}
}

TEST( NStringResize, resizeMaintainsNullTermination )
{
	str_lib::String str = "abc";
	str.resize( 6, 'x' );

	SCOPED_TRACE( "Check null-terminator after resize" );
	ASSERT_EQ( str.cstr()[str.size()], '\0' );
}

#endif // !NSTRING_RESIZE_GT_HPP
