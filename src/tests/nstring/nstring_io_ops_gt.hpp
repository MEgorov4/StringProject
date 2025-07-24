#ifndef NSTRING_io_OPS_GT_HPP
#define NSTRING_io_OPS_GT_HPP

#include <sstream>
#include <gtest/gtest.h>

#include "nstring.h"

TEST(NStringIStream, readSingleWord)
{
	std::istringstream iss("hello");
	nstring::String str;

	iss >> str;

	SCOPED_TRACE("Read single token");
	ASSERT_TRUE(!strcmp(str.cstr(), "hello"));
	ASSERT_EQ(str.size(), 5);
	ASSERT_TRUE(iss.eof());
}

TEST(NStringIStream, skipLeadingSpaces)
{
	std::istringstream iss("   \t  world");
	nstring::String str;

	iss >> str;

	SCOPED_TRACE("Leading whitespace must be skipped");
	ASSERT_TRUE(!strcmp(str.cstr(), "world"));
	ASSERT_EQ(str.size(), 5);
}

TEST(NStringIStream, stopAtWhitespace)
{
	std::istringstream iss("foo bar");
	nstring::String first;
	nstring::String second;

	iss >> first >> second;

	SCOPED_TRACE("Operator>> stops at first whitespace");
	ASSERT_TRUE(!strcmp(first.cstr(), "foo"));
	ASSERT_TRUE(!strcmp(second.cstr(), "bar"));
}

TEST(NStringIStream, readEmptyStreamSetsFailbit)
{
	std::istringstream iss("");
	nstring::String str;

	iss >> str;

	SCOPED_TRACE("Empty stream should set failbit");
	ASSERT_TRUE(iss.fail());
	ASSERT_EQ(str.size(), 0);
}

TEST(NStringIStream, readUntilEof)
{
	std::istringstream iss("one two");
	nstring::String a, b;

	iss >> a >> b;

	SCOPED_TRACE("Reading two tokens reaches eof");
	ASSERT_TRUE(!strcmp(a.cstr(), "one"));
	ASSERT_TRUE(!strcmp(b.cstr(), "two"));
	ASSERT_TRUE(iss.eof());
}

#endif  // NSTRING_OSTREAM_OPS_GT_HPP
