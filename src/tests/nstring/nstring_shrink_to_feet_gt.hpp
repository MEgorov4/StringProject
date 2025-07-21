#ifndef NSTRING_SHRING_TO_FEET_HPP
#define NSTRING_SHRING_TO_FEET_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringShrinkToFit, shrinkToFitDoesNothingWhenAlreadyTight )
{
	str_lib::String str = "abc";
	str.shrink_to_fit();

	SCOPED_TRACE( "shrink_to_fit should not change already tight buffer" );
	ASSERT_EQ( str.size(), 3 );
	ASSERT_EQ( str.capacity(), 3 );
	ASSERT_TRUE( !strcmp( str.cstr(), "abc" ) );
}

TEST( NStringShrinkToFit, shrinkToFitReducesCapacity )
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

TEST( NStringShrinkToFit, shrinkToFitPreservesContent )
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

TEST( NStringShrinkToFit, shrinkToFitMultipleCalls )
{
	str_lib::String str = "lazyvim";
	str.reserve( 64 );
	str.shrink_to_fit();
	str.shrink_to_fit(); // снова
	str.shrink_to_fit(); // ещё раз

	SCOPED_TRACE( "Multiple shrink_to_fit calls should be safe" );
	ASSERT_EQ( str.size(), 7 );
	ASSERT_EQ( str.capacity(), 7 );
	ASSERT_TRUE( !strcmp( str.cstr(), "lazyvim" ) );
}

TEST( NStringShrinkToFit, shrinkToFitEmptyString )
{
	str_lib::String str;
	str.shrink_to_fit();

	SCOPED_TRACE( "shrink_to_fit on empty string should result in capacity 0 or base" );
	ASSERT_EQ( str.size(), 0 );
	ASSERT_TRUE( str.cstr()[0] == '\0' );
}

#endif // !NSTRING_SHRING_TO_FEET_HPP
