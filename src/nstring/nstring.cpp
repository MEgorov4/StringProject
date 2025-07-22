#include "nstring.h"
#include <cctype>
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
		if( MAX_CAPACITY < count )
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
		size_t size = strlen( cstr );
		m_capacity  = BASE_CAPACITY >= size ? BASE_CAPACITY : size;
		m_size      = size;

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
			if( m_capacity >= rhs.m_size )
			{
				memcpy( m_buffer, rhs.m_buffer, rhs.m_size );

				m_size           = rhs.m_size;
				m_buffer[m_size] = '\0';
			}
			else
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
		}
		return *this;
	}

	String& String::operator=( String&& rhs ) noexcept
	{
		if( &rhs != this )
		{
			free( m_buffer );
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

	char& String::at( size_t index )
	{
		if( index >= m_size )
		{
			throw std::out_of_range( "index out of range" );
		}
		return m_buffer[index];
	}

	const char& String::at( size_t index ) const
	{
		if( index >= m_size )
		{
			throw std::out_of_range( "index out of range" );
		}
		return m_buffer[index];
	};

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
	String& String::operator+=( const char* rhs )
	{
		if( rhs == nullptr )
		{
			throw std::invalid_argument( "Append with null is not valid" );
		}
		String temp( rhs );
		return *this += temp;
	};

	void String::resize( size_t size, char ch )
	{
		if( m_size == size )
		{
			return;
		}

		ensure_capacity( size );

		if( m_size < size )
		{
			memset( m_buffer + m_size, ch, size - m_size );
		}

		m_size           = size;
		m_buffer[m_size] = '\0';
	}

	void String::ensure_capacity( size_t newSize )
	{
		if( m_capacity >= newSize )
		{
			return;
		}

		if( MAX_CAPACITY < newSize )
		{
			throw std::length_error( "Max capacity overflow" );
		}

		if( MAX_CAPACITY < ( newSize * GROW_COEF ) )
		{
			throw std::length_error( "Grow capacity overflow" );
		}

		size_t newCapacity = newSize * GROW_COEF;
		char*  newBuffer   = static_cast< char* >( realloc( m_buffer, newCapacity + 1 ) );
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

		if( MAX_CAPACITY <= capacity )
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

	void String::push_back( char ch )
	{
		ensure_capacity( m_size + 1 );

		m_buffer[m_size++] = ch;
		m_buffer[m_size]   = '\0';
	}

	void String::clear()
	{
		if( m_size == 0 )
			return;

		m_size           = 0;
		m_buffer[m_size] = '\0';
	}

	std::istream& operator>>( std::istream& in, String& rhs )
	{
		rhs.clear();

		char ch;

		while( in.get( ch ) && std::isspace( ch ) )
		{
		};

		if( !in )
			return in;

		do
		{
			rhs.push_back( ch );
		} while( in.get( ch ) && !std::isspace( ch ) );

		if( in && std::isspace( ch ) )
		{
			in.unget();
		}
		return in;
	}

	std::ostream& operator<<( std::ostream& out, const String& rhs ) noexcept
	{
		return out << rhs.cstr();
	}

	String operator+( const String& lhs, const String& rhs )
	{
		String result; // no SSO, just vibes :)
		result.reserve( lhs.size() + rhs.size() );
		result = lhs;
		result += rhs;
		return result;
	}

	String operator+( const String& lhs, const char* rhs )
	{
		String result;
		result.reserve( lhs.size() + strlen( rhs ) );
		result += lhs;
		result += rhs;
		return result;
	}

	String operator+( const char* lhs, const String& rhs )
	{
		String result;
		result.reserve( strlen( lhs ) + rhs.size() );
		result += lhs;
		result += rhs;
		return result;
	}

	bool operator==( const String& lhs, const String& rhs ) noexcept
	{
		return strcmp( lhs.cstr(), rhs.cstr() ) == 0;
	}

	bool operator==( const String& lhs, const char* rhs ) noexcept
	{
		return strcmp( lhs.cstr(), rhs ) == 0;
	}

	bool operator==( const char* lhs, const String& rhs ) noexcept
	{
		return strcmp( lhs, rhs.cstr() ) == 0;
	}

	bool operator!=( const String& lhs, const String& rhs ) noexcept
	{
		return !( lhs == rhs );
	}

	bool operator!=( const String& lhs, const char* rhs ) noexcept
	{
		return !( lhs == rhs );
	}

	bool operator!=( const char* lhs, const String& rhs ) noexcept
	{
		return !( lhs == rhs );
	}

	bool operator<( const String& lhs, const String& rhs ) noexcept
	{
		return strcmp( lhs.cstr(), rhs.cstr() ) < 0;
	}

	bool operator<( const String& lhs, const char* rhs ) noexcept
	{
		return strcmp( lhs.cstr(), rhs ) < 0;
	}

	bool operator<( const char* lhs, const String& rhs ) noexcept
	{
		return strcmp( lhs, rhs.cstr() ) < 0;
	}

	bool operator<=( const String& lhs, const String& rhs ) noexcept
	{
		return ( lhs < rhs ) || ( lhs == rhs );
	}

	bool operator<=( const String& lhs, const char* rhs ) noexcept
	{
		return ( lhs < rhs ) || ( lhs == rhs );
	}

	bool operator<=( const char* lhs, const String& rhs ) noexcept
	{
		return ( lhs < rhs ) || ( lhs == rhs );
	}

	bool operator>( const String& lhs, const String& rhs ) noexcept
	{
		return !( lhs <= rhs );
	}

	bool operator>( const String& lhs, const char* rhs ) noexcept
	{
		return !( lhs <= rhs );
	}

	bool operator>( const char* lhs, const String& rhs ) noexcept
	{
		return !( lhs <= rhs );
	}

	bool operator>=( const String& lhs, const String& rhs ) noexcept
	{
		return !( lhs < rhs );
	}

	bool operator>=( const String& lhs, const char* rhs ) noexcept
	{
		return !( lhs < rhs );
	}

	bool operator>=( const char* lhs, const String& rhs ) noexcept
	{
		return !( lhs < rhs );
	};
} // namespace str_lib
