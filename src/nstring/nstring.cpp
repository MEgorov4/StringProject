#include "nstring.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>
#include <utility>

namespace str_lib {

	String::String() : m_capacity( BASE_CAPACITY ), m_size( 0 )
	{
		char* buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
		if( buffer == nullptr )
		{
			throw std::bad_alloc();
		}

		m_buffer         = buffer;
		m_buffer[m_size] = '\0';
	}

	String::String( size_t count, char ch ) : m_capacity( count ), m_size( count )
	{
		if( SIZE_MAX - 1 < count )
		{
			throw std::length_error( "Max capacity overflow" );
		}

		char* buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
		if( buffer == nullptr )
		{
			throw std::bad_alloc();
		}

		memset( buffer, ch, m_size );

		m_buffer         = buffer;
		m_buffer[m_size] = '\0';
	};

	String::String( const char* cstr )
	{
		if( cstr == nullptr )
		{
			throw std::invalid_argument( "Construction from null is not valid" );
		}

		m_capacity = strlen( cstr );
		m_size     = m_capacity;

		char* buffer = static_cast< char* >( malloc( m_capacity + 1 ) );
		if( buffer == nullptr )
		{
			throw std::bad_alloc();
		}

		memcpy( buffer, cstr, m_size );

		m_buffer         = buffer;
		m_buffer[m_size] = '\0';
	}

	String::String( const String& other ) : String( other.cstr() ) {}

	String::String( String&& other ) noexcept
	    : m_buffer( other.m_buffer ), m_capacity( other.m_capacity ), m_size( other.m_size )
	{
		other.m_buffer   = nullptr;
		other.m_size     = 0;
		other.m_capacity = 0;
	}

	String::~String()
	{
		free( m_buffer );
	}

	String& String::operator=( const String& rhs )
	{
		if( &rhs != this )
		{
			char* buffer = static_cast< char* >( malloc( rhs.m_capacity + 1 ) );
			if( buffer == nullptr )
			{
				throw std::bad_alloc();
			}

			memcpy( buffer, rhs.m_buffer, rhs.m_size );

			free( m_buffer );

			m_buffer         = buffer;
			m_capacity       = rhs.m_capacity;
			m_size           = rhs.m_size;
			m_buffer[m_size] = '\0';
		}
		return *this;
	}

	String& String::operator=( String&& rhs ) noexcept
	{
		if( &rhs != this )
		{
			m_buffer       = rhs.m_buffer;
			m_capacity     = rhs.m_capacity;
			m_size         = rhs.m_size;
			rhs.m_buffer   = nullptr;
			rhs.m_capacity = 0;
			rhs.m_size     = 0;
		}
		return *this;
	}

	String& String::operator=( const char* cstr )
	{
		if( m_buffer != cstr )
		{
			String newString( cstr );
			*this = std::move( newString );
		}

		return *this;
	}

	String& String::operator+=( const String& rhs )
	{
		if( this == &rhs )
		{
			String temp( rhs );
			return *this += temp;
		}

		ensure_capacity( m_size + rhs.size() );

		memcpy( m_buffer + m_size, rhs.m_buffer, rhs.size() );

		m_size += rhs.size();
		m_buffer[m_size] = '\0';

		return *this;
	}

	void String::resize( size_t size, char ch )
	{
		if( m_size == size )
		{
			return;
		}

		ensure_capacity( size );

		if( m_size > size )
		{
			memset( m_buffer + size, ch, m_size - size );
		}
		else
		{
			memset( m_buffer + m_size, ch, size - m_size );
		}

		m_size = size;
	}

	void String::ensure_capacity( size_t size )
	{
		if( m_capacity >= size )
		{
			return;
		}

		if( SIZE_MAX < size )
		{
			throw std::length_error( "Max capacity overflow" );
		}

		if( SIZE_MAX / 2 < size )
		{
			throw std::length_error( "Grow capacity overflow" );
		}

		// calc increased capacity
		size_t newCapacity = size * GROW_COEF;

		// try reallocate with new capacity
		char* newBuffer = static_cast< char* >( realloc( m_buffer, newCapacity + 1 ) );
		if( newBuffer == nullptr )
		{
			throw std::bad_alloc();
		}

		m_buffer   = newBuffer;
		m_capacity = newCapacity;
	}

	void String::reserve( size_t capacity )
	{
		if( m_capacity >= capacity )
		{
			return;
		}

		if( SIZE_MAX <= capacity )
		{
			throw std::length_error( "Max capacity overflow" );
		}

		char* buffer = static_cast< char* >( realloc( m_buffer, capacity + 1 ) );
		if( buffer == nullptr )
		{
			throw std::bad_alloc();
		}

		m_buffer   = buffer;
		m_capacity = capacity;
	}

	void String::shrink_to_fit()
	{
		if( m_capacity == m_size )
		{
			return;
		}

		char* buffer = static_cast< char* >( realloc( m_buffer, m_size + 1 ) );
		if( buffer == nullptr )
		{
			throw std::bad_alloc();
		}

		m_capacity = m_size;
		m_buffer   = buffer;
	}

	String operator+( const String& lhs, const String& rhs )
	{
		String result( lhs );
		result.reserve( lhs.size() + rhs.size() );
		result += rhs;
		return result;
	}

	String operator+( const String& lhs, const char* rhs )
	{
		return String( lhs ) += rhs;
	}
	String operator+( const char* lhs, const String& rhs )
	{
		return String( lhs ) += rhs;
	}
} // namespace str_lib
