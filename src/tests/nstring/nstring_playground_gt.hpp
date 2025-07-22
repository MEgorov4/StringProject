#ifndef NSTRING_PLAYGROUND_GT_HPP
#define NSTRING_PLAYGROUND_GT_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringPlayground, selfAssignment )
{
	str_lib::String s = "123";
	s                 = s;

	SCOPED_TRACE( "Self-assignment should not corrupt content" );
	ASSERT_EQ( s.size(), 3 );
	ASSERT_TRUE( !strcmp( s.cstr(), "123" ) );
}

TEST( NStringPlayground, appendNullShouldThrow )
{
	str_lib::String s        = "test";
	const char*     nullCStr = nullptr;

	SCOPED_TRACE( "Appending null c-string should throw" );
	ASSERT_THROW( s += nullCStr, std::invalid_argument );
}

TEST( NStringPlayground, assignmentFromNullShouldThrow )
{
	const char* nullCStr = nullptr;

	SCOPED_TRACE( "Constructing from null should throw" );
	ASSERT_THROW( str_lib::String s( nullCStr ), std::invalid_argument );
}

TEST( NStringPlayground, largeResizeShouldThrow )
{
	str_lib::String s = "ok";

	SCOPED_TRACE( "Resizing beyond max capacity should throw" );
	ASSERT_THROW( s.resize( str_lib::String::max_capacity() + 1 ), std::length_error );
}

TEST( NStringPlayground, lengthEqualsSizeInvariant )
{
	for( size_t i = 0; i < 1000; ++i )
	{
		size_t          len = size_t( rand() % 1000 );
		str_lib::String s( len, 'x' );
		ASSERT_EQ( strlen( s.cstr() ), s.size() );
	}
}

TEST( NStringPlayground, randomAppendChainPreservesSize )
{
	str_lib::String s;
	std::string     ref;

	for( size_t i = 0; i < 100; ++i )
	{
		size_t          len = size_t( 1 + rand() % 20 );
		std::string     part( len, 'a' + static_cast< char >( rand() % 26 ) );
		str_lib::String frag( part.c_str() );

		s += frag;
		ref += part;
	}

	ASSERT_EQ( s.size(), ref.size() );
	ASSERT_STREQ( s.cstr(), ref.c_str() );
}

TEST( NStringPlayground, shrinkToFitPreservesData )
{
	str_lib::String s( "abcdefghij" );
	s.reserve( 200 );
	size_t cap_before = s.capacity();

	s.shrink_to_fit();
	ASSERT_EQ( strlen( s.cstr() ), s.size() );
	ASSERT_STREQ( s.cstr(), "abcdefghij" );
	ASSERT_LE( s.capacity(), cap_before );
}

TEST( NStringPlayground, multipleSelfAppendGrowsCorrectly )
{
	str_lib::String s( "abc" );
	s += s;
	s += s;

	ASSERT_STREQ( s.cstr(), "abcabcabcabc" );
	ASSERT_EQ( s.size(), 12 );
}

#endif // NSTRING_PLAYGROUND_GT_HPP
