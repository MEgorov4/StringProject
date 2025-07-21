#ifndef NSTRING_SHRING_TO_FEET_HPP
#define NSTRING_SHRING_TO_FEET_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringOps, shrinkToFitDoesNothingWhenAlreadyTight )
{
	str_lib::String str = "abc";
	str.shrink_to_fit();

	SCOPED_TRACE( "shrink_to_fit should not change already tight buffer" );
	ASSERT_EQ( str.size(), 3 );
	ASSERT_EQ( str.capacity(), 3 );
	ASSERT_TRUE( !strcmp( str.cstr(), "abc" ) );
}

TEST( NStringOps, shrinkToFitReducesCapacity )
{
	str_lib::String str = "abc";
	str.reserve( 100 );

	size_t oldCap = str.capacity();
	ASSERT_GT( oldCap, str.size() );

	str.shrink_to_fit();

	SCOPED_TRACE( "shrink_to_fit should reduce capacity to size" );
	ASSERT_EQ( str.size(), 3 );
	ASSERT_EQ( str.capacity(), 3 );
	ASSERT_TRUE( !strcmp( str.cstr(), "abc" ) );
}

TEST( NStringOps, shrinkToFitPreservesContent )
{
	str_lib::String str = "hello world!";
	str.reserve( 200 );

	str.shrink_to_fit();

	SCOPED_TRACE( "Content must be preserved after shrink_to_fit" );
	ASSERT_TRUE( !strcmp( str.cstr(), "hello world!" ) );
	ASSERT_NE( str.cstr(), nullptr );
	ASSERT_EQ( str.size(), strlen( "hello world!" ) );
	ASSERT_EQ( str.capacity(), strlen( "hello world!" ) );
}
#endif // !NSTRING_SHRING_TO_FEET_HPP
