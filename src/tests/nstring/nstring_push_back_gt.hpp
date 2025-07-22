#ifndef NSTRING_PUSH_BACK_GT_HPP
#define NSTRING_PUSH_BACK_GT_HPP
#include "../../nstring/nstring.h"
#include "gtest/gtest.h"
using str_lib::String;

TEST( NStringPushBack, pushToEmpty )
{
	String s;
	s.push_back( 'A' );

	SCOPED_TRACE( "Push back into empty string" );
	ASSERT_EQ( s.size(), 1 );
	ASSERT_TRUE( !strcmp( s.cstr(), "A" ) );
}

TEST( NStringPushBack, pushSeveralChars )
{
	String s = "ab";
	s.push_back( 'c' );
	s.push_back( 'd' );

	SCOPED_TRACE( "Push multiple characters sequentially" );
	ASSERT_EQ( s.size(), 4 );
	ASSERT_TRUE( !strcmp( s.cstr(), "abcd" ) );
}

TEST( NStringPushBack, capacityGrowth )
{
	String       s;
	const size_t initial_cap = s.capacity();

	// заполняем до превышения изначальной ёмкости
	for( size_t i = 0; i < initial_cap + 5; ++i )
		s.push_back( 'x' );

	SCOPED_TRACE( "Push back triggers realloc when capacity exceeded" );
	ASSERT_GE( s.capacity(), initial_cap * String::grow_coef() );
	ASSERT_EQ( s.size(), initial_cap + 5 );
	for( size_t i = 0; i < s.size(); ++i )
		ASSERT_EQ( s[i], 'x' );
}

TEST( NStringPushBack, afterReserveNoRealloc )
{
	String s;
	s.reserve( 64 );
	const size_t cap_before = s.capacity();

	for( int i = 0; i < 32; ++i )
		s.push_back( 'y' );

	SCOPED_TRACE( "No reallocation after manual reserve" );
	ASSERT_EQ( s.capacity(), cap_before );
	ASSERT_EQ( s.size(), 32 );
}

#endif // !NSTRING_PUSH_BACK_GT_HPP
