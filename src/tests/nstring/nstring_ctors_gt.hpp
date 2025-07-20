#ifndef NSTRING_CTORS_GT_HPP
#define NSTRING_CTORS_GT_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"

TEST( NStringCtors, defaultCtor )
{
	str_lib::String str;
	SCOPED_TRACE( "Check size of empty string" );
	ASSERT_EQ( str.size(), 0 );

	SCOPED_TRACE( "Check capacity of empty string" );
	ASSERT_EQ( str.capacity(), 15 );

	SCOPED_TRACE( "Check [0] to equality null-terminant" );
	ASSERT_EQ( str.cstr()[0], '\0' );
}

TEST( NStringCtors, fromCstrCtor )
{
	const char*     cstr = "abc";
	str_lib::String str  = cstr;

	SCOPED_TRACE( "Compare base cstr to cstr colected from str_lib::String::cstr()" );
	ASSERT_TRUE( !strcmp( str.cstr(), cstr ) );
	ASSERT_EQ( str.size(), strlen( cstr ) );
	ASSERT_EQ( str.capacity(), strlen( cstr ) );

	const char*     bigCstr = "l;aksdfj;laskdl;jfjs;ladkf;jklsadljfk;jlas;kdfj;"
	                          "lkasldj;kfklj;saldk;jf;jaslkdfasld;kfjja;slkdf";
	str_lib::String bigStr( bigCstr );

	SCOPED_TRACE( "Compare base cstr to cstr collected from str_lib::String" );
	ASSERT_TRUE( !strcmp( bigStr.cstr(), bigCstr ) );
	ASSERT_EQ( bigStr.size(), strlen( bigCstr ) );
	ASSERT_EQ( bigStr.capacity(), strlen( bigCstr ) );
}

TEST( NStringCtors, copyCtor )
{
	str_lib::String original( "abc" );
	str_lib::String copyed( original );

	SCOPED_TRACE( "Check equality of data if str_lib::String constructed by "
	              "another str_lib::String" );
	ASSERT_TRUE( !strcmp( original.cstr(), copyed.cstr() ) );

	SCOPED_TRACE( "Check equality of size" );
	ASSERT_EQ( original.size(), copyed.size() );

	SCOPED_TRACE( "Check equality of capacity" );
	ASSERT_EQ( original.capacity(), copyed.capacity() );

	SCOPED_TRACE( "Check copyed str have diff in data-pointer value" );
	ASSERT_NE( original.cstr(), copyed.cstr() );
}

TEST( NStringCtors, moveCtor )
{
	str_lib::String str( str_lib::String( "abcdef" ) );

	SCOPED_TRACE( "Check data" );
	ASSERT_TRUE( !strcmp( str.cstr(), "abcdef" ) );

	SCOPED_TRACE( "Check size" );
	ASSERT_EQ( str.size(), 6 );

	SCOPED_TRACE( "Check capacity" );
	ASSERT_EQ( str.capacity(), 6 );

	str_lib::String original( "abc" );
	str_lib::String moved( std::move( original ) );

	SCOPED_TRACE( "Check moved string data to equal 0 health" );
	ASSERT_EQ( original.cstr(), nullptr );

	SCOPED_TRACE( "Check data" );
	ASSERT_TRUE( !strcmp( moved.cstr(), "abc" ) );

	SCOPED_TRACE( "Check capacity" );
	ASSERT_EQ( moved.size(), 3 );

	SCOPED_TRACE( "Check capacity" );
	ASSERT_EQ( moved.capacity(), 3 );
}

#endif
