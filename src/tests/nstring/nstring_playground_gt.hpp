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

#endif // NSTRING_PLAYGROUND_GT_HPP
