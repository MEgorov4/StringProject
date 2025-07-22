#ifndef NSTRING_OPS_GT_HPP
#define NSTRING_OPS_GT_HPP

#include "../../nstring/nstring.h"
#include "gtest/gtest.h"
#include <cstddef>

TEST( NStringOps, assignFromCstr )
{
	str_lib::String str;
	str = "hello";

	SCOPED_TRACE( "Check content after assignment from const char*" );
	ASSERT_TRUE( !strcmp( str.cstr(), "hello" ) );

	SCOPED_TRACE( "Check size after assignment" );
	ASSERT_EQ( str.size(), 5 );

	SCOPED_TRACE( "Check capacity after assignment" );
	ASSERT_EQ( str.capacity(), str_lib::String::base_capacity() );
}

TEST( NStringOps, copyAssignment )
{
	str_lib::String original( "world" );
	str_lib::String copyed;
	copyed = original;

	SCOPED_TRACE( "Check content equality after copy assignment" );
	ASSERT_TRUE( !strcmp( original.cstr(), copyed.cstr() ) );

	SCOPED_TRACE( "Check size equality" );
	ASSERT_EQ( original.size(), copyed.size() );

	SCOPED_TRACE( "Check capacity equality" );
	ASSERT_EQ( original.capacity(), str_lib::String::base_capacity() );

	SCOPED_TRACE( "Ensure deep copy (different buffers)" );
	ASSERT_NE( original.cstr(), copyed.cstr() );
}

TEST( NStringOps, moveAssignment )
{
	str_lib::String original( "data" );
	str_lib::String moved;
	moved = std::move( original );

	SCOPED_TRACE( "Check moved-from string is null" );
	ASSERT_EQ( original.cstr(), nullptr );
	ASSERT_EQ( original.size(), 0 );
	ASSERT_EQ( original.capacity(), 0 );

	SCOPED_TRACE( "Check moved-to string content" );
	ASSERT_TRUE( !strcmp( moved.cstr(), "data" ) );

	SCOPED_TRACE( "Check moved-to string size" );
	ASSERT_EQ( moved.size(), 4 );

	SCOPED_TRACE( "Check moved-to string capacity" );
	ASSERT_EQ( moved.capacity(), str_lib::String::base_capacity() );
}

TEST( NStringOps, subscriptOperator )
{
	str_lib::String s = { "abcdef" };

	SCOPED_TRACE( "Access and verify each character by index" );
	ASSERT_EQ( s[0], 'a' );
	ASSERT_EQ( s[1], 'b' );
	ASSERT_EQ( s[2], 'c' );
	ASSERT_EQ( s[3], 'd' );
	ASSERT_EQ( s[4], 'e' );
	ASSERT_EQ( s[5], 'f' );

	SCOPED_TRACE( "Modify characters via non-const operator[]" );
	s[0] = 'x';
	s[5] = 'z';

	ASSERT_EQ( s[0], 'x' );
	ASSERT_EQ( s[5], 'z' );
	ASSERT_TRUE( !strcmp( s.cstr(), "xbcdez" ) );

	SCOPED_TRACE( "Check const access to operator[]" );
	const str_lib::String& constRef = s;
	ASSERT_EQ( constRef[1], 'b' );
	ASSERT_EQ( constRef[2], 'c' );
	ASSERT_EQ( constRef[3], 'd' );
	ASSERT_EQ( constRef[4], 'e' );
}

TEST( NStringOps, plusEqualWithString )
{
	str_lib::String a = "abc";
	str_lib::String b = "def";
	a += b;

	SCOPED_TRACE( "Check content after += with another String" );
	ASSERT_TRUE( !strcmp( a.cstr(), "abcdef" ) );
	ASSERT_EQ( a.size(), 6 );
}

TEST( NStringOps, plusEqualWithCstr )
{
	str_lib::String a = "123";
	a += "456";

	SCOPED_TRACE( "Check content after += with const char*" );
	ASSERT_TRUE( !strcmp( a.cstr(), "123456" ) );
	ASSERT_EQ( a.size(), 6 );
}

TEST( NStringOps, plusEqualSelfAppend )
{
	str_lib::String a = "xy";
	a += a;

	SCOPED_TRACE( "Check content after self-append" );
	ASSERT_TRUE( !strcmp( a.cstr(), "xyxy" ) );
	ASSERT_EQ( a.size(), 4 );
}

TEST( NStringOps, plusEqualMultiple )
{
	str_lib::String a = "A";
	str_lib::String b = "B";
	str_lib::String c = "C";

	a += b += c;

	SCOPED_TRACE( "Check chained += result" );
	ASSERT_TRUE( !strcmp( b.cstr(), "BC" ) );
	ASSERT_TRUE( !strcmp( a.cstr(), "ABC" ) );
}

TEST( NStringOps, plusEqualTriggersRealloc )
{
	str_lib::String a       = "short";
	const char*     longStr = "this is a very long string to trigger reallocation";

	size_t oldCapacity = a.capacity();
	a += longStr;

	SCOPED_TRACE( "Check content after += with long const char*" );
	ASSERT_TRUE( !strcmp( a.cstr(), "shortthis is a very long string to trigger reallocation" ) );

	SCOPED_TRACE( "Check updated size after += long string" );
	ASSERT_EQ( a.size(), strlen( "short" ) + strlen( longStr ) );

	SCOPED_TRACE( "Check that capacity has grown" );
	ASSERT_GE( a.capacity(), a.size() );
	ASSERT_GT( a.capacity(), oldCapacity );
}

TEST( NStringOps, plusEqualOperatorRvalueAppendToEmpty )
{
	str_lib::String a; // пустая строка
	a += str_lib::String( "MoveMe" );

	SCOPED_TRACE( "Append r-value to empty string" );
	ASSERT_STREQ( a.cstr(), "MoveMe" );
	ASSERT_EQ( a.size(), strlen( "MoveMe" ) );
}

TEST( NStringOps, plusEqualOperatorRvalueAppendToNonEmpty )
{
	str_lib::String a = "Start-";
	a += str_lib::String( "End" );

	SCOPED_TRACE( "Append r-value to non-empty string" );
	ASSERT_STREQ( a.cstr(), "Start-End" );
	ASSERT_EQ( a.size(), strlen( "Start-End" ) );
}

#endif
