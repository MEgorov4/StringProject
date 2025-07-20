#include "nstring.h"
#include <cstdlib>
#include <cstring>
#include <utility>

using namespace str_lib;

String::String() : m_capacity( BASE_CAPACITY ), m_size( 0 )
{
	// alloc [data-15b][null-term-1b]
	m_buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
	// place null-term in first place
	m_buffer[m_size] = '\0';
}

String::String( const char* cstr ) : m_capacity( strlen( cstr ) ), m_size( m_capacity )
{
	// alloc [strlen(cstr)][null-term-1b]
	m_buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
	// copy data from cstr [strlen(cstr)] -> [m_buffer.size()][m_capacity -
	// size][null-term]
	memcpy( m_buffer, cstr, m_size );
	// place null-term in last place
	m_buffer[m_size] = '\0';
};

String::String( const String& other ) : String( other.cstr() )
{
	// delligate to fromCSTR constructor
}

String::String( String&& other ) noexcept
    : m_buffer( other.m_buffer ), m_capacity( other.m_capacity ), m_size( other.m_size )
{
	// Cearfuly kill r-value`s data-pointer
	other.m_buffer = nullptr;
};

String::~String()
{
	free( m_buffer );
}

String& String::operator=( const String& rhs )
{
	// check assign to yourself
	if( &rhs != this )
	{
		// clear own-data
		free( m_buffer );
		// bagage capacity and size
		m_capacity = rhs.m_capacity;
		m_size     = rhs.m_size;
		// alloc [newCapacity-b][null-term-1b]
		m_buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
		// fill copy data from rhs.m_buffer to m_buffer by new m_size
		memcpy( m_buffer, rhs.m_buffer, m_size );
		// place null-term in last place
		m_buffer[m_size] = '\0';
	}
	return *this;
};

String& String::operator=( String&& rhs ) noexcept
{
	// check equality yourself
	if( &rhs != this )
	{
		// swap data
		std::swap( m_capacity, rhs.m_capacity );
		std::swap( m_size, rhs.m_size );
		std::swap( m_buffer, rhs.m_buffer );
	}
	return *this;
};

str_lib::String& str_lib::String::operator=( const char* cstr )
{
	// check equality yourself`s buffer and cstr
	if( m_buffer != cstr )
	{
		// using fromCSTRCtor
		String newString( cstr );
		// using moveAssignment
		*this = std::move( newString );
	}

	return *this;
};

str_lib::String& str_lib::String::operator+=( const String& rhs )
{
	// Check self increment
	if( this == &rhs )
	{
		String temp( rhs );
		return *this += temp;
	}
	// check actual String size + incremented String size <= capacity of this String
	// [m_size-b][rhs.m_size-b][m_capacity - (m_size + rhs.m_size)-b]
	if( m_size + rhs.size() > m_capacity )
	{
		m_capacity      = ( m_size + rhs.m_size ) * 2; // :FIXME: possible capacity overflow
		char* newBuffer = static_cast< char* >( realloc( m_buffer, m_capacity + 1 ) );
		if( newBuffer )
		{
			m_buffer = newBuffer;
		}
	}
	// copy data from rhs.m_buffer to place after current String data ended
	memcpy( m_buffer + m_size, rhs.m_buffer, rhs.size() );
	m_size += rhs.size();
	m_buffer[m_size] = '\0';

	return *this;
};
