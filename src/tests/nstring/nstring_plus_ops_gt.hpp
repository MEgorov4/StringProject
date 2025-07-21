#ifndef NSTRING_PLUS_OPS_GT_HPP
#define NSTRING_PLUS_OPS_GT_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringOps, plusOperatorStringAndString )
{
	str_lib::String a      = "Hello, ";
	str_lib::String b      = "World!";
	str_lib::String result = a + b;

	SCOPED_TRACE( "Check result of String + String" );
	ASSERT_NE( strcmp( result.cstr(), "Hello, " ), 0 );
	ASSERT_NE( strcmp( result.cstr(), "World!" ), 0 );
	ASSERT_EQ( strcmp( result.cstr(), "Hello, World!" ), 0 );
	ASSERT_EQ( result.size(), strlen( "Hello, World!" ) );
}

TEST( NStringOps, plusOperatorStringAndCstr )
{
	str_lib::String a   = "Number: ";
	const char*     num = "42";

	str_lib::String result = a + num;

	SCOPED_TRACE( "Check result of String + const char*" );
	ASSERT_TRUE( !strcmp( result.cstr(), "Number: 42" ) );
	ASSERT_EQ( result.size(), strlen( "Number: 42" ) );
}

TEST( NStringOps, plusOperatorCstrAndString )
{
	const char*     prefix = "Value: ";
	str_lib::String b      = "3.14";

	str_lib::String result = prefix + b;

	SCOPED_TRACE( "Check result of const char* + String" );
	ASSERT_TRUE( !strcmp( result.cstr(), "Value: 3.14" ) );
	ASSERT_EQ( result.size(), strlen( "Value: 3.14" ) );
}

#endif // !NSTRING_PLUS_OPS_GT_HPP
