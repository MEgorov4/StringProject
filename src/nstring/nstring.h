#ifndef STRING_H
#define STRING_H

#include <cstdint>
#include <istream>
#include <ostream>
#include <stddef.h>

namespace str_lib {

	class String
	{
	public:
		/// ctors/dtor
		String();
		explicit String( size_t count, char c );
		String( const char* cstr );
		String( const String& other );
		String( String&& other ) noexcept;
		~String();

		String& operator=( const String& rhs );
		String& operator=( String&& rhs ) noexcept;
		String& operator=( const char* cstr );

		String& operator+=( const String& rhs );
		String& operator+=( String&& rhs );
		String& operator+=( const char* rhs );

		/// access
		char&       operator[]( size_t index ) { return m_buffer[index]; }
		const char& operator[]( size_t index ) const { return m_buffer[index]; }

		/// validate-access
		char&       at( size_t index );
		const char& at( size_t index ) const;

		/// random-access
		char*       begin() noexcept { return m_buffer; }
		const char* begin() const noexcept { return m_buffer; }
		char*       end() noexcept { return m_buffer + m_size; }
		const char* end() const noexcept { return m_buffer + m_size; }

		const char* cstr() const noexcept { return m_buffer; }
		size_t      size() const noexcept { return m_size; }
		size_t      capacity() const noexcept { return m_capacity; }

		void resize( size_t size, char ch = '\0' );
		void reserve( size_t capacity );
		void shrink_to_fit();

		void clear();
		void push_back( char ch );

	public:
		static constexpr size_t max_capacity() noexcept { return MAX_CAPACITY; }
		static constexpr size_t grow_coef() noexcept { return GROW_COEF; }
		static constexpr size_t base_capacity() noexcept { return BASE_CAPACITY; }

	private:
		void ensure_capacity( size_t newSize );

	private:
		char*  m_buffer;
		size_t m_capacity;
		size_t m_size;

		static constexpr size_t BASE_CAPACITY = 15;
		static constexpr size_t GROW_COEF     = 2;
		static constexpr size_t MAX_CAPACITY  = SIZE_MAX / 4;
	};

	// ostream/istream ops
	std::istream& operator>>( std::istream& in, String& rhs );
	std::ostream& operator<<( std::ostream& stream, const String& rhs ) noexcept;

	// plus operator
	String operator+( const String& lhs, const String& rhs );
	String operator+( const String& lhs, const char* rhs );
	String operator+( const char* lhs, const String& rhs );

	// eq operator
	bool operator==( const String& lhs, const String& rhs ) noexcept;
	bool operator==( const String& lhs, const char* rhs ) noexcept;
	bool operator==( const char* lhs, const String& rhs ) noexcept;

	// non-eq operator
	bool operator!=( const String& lhs, const String& rhs ) noexcept;
	bool operator!=( const String& lhs, const char* rhs ) noexcept;
	bool operator!=( const char* lhs, const String& rhs ) noexcept;

	// less operator
	bool operator<( const String& lhs, const String& rhs ) noexcept;
	bool operator<( const String& lhs, const char* rhs ) noexcept;
	bool operator<( const char* lhs, const String& rhs ) noexcept;

	// less-eq operator
	bool operator<=( const String& lhs, const String& rhs ) noexcept;
	bool operator<=( const String& lhs, const char* rhs ) noexcept;
	bool operator<=( const char* lhs, const String& rhs ) noexcept;

	// greater operator
	bool operator>( const String& lhs, const String& rhs ) noexcept;
	bool operator>( const String& lhs, const char* rhs ) noexcept;
	bool operator>( const char* lhs, const String& rhs ) noexcept;

	// greater-eq operator
	bool operator>=( const String& lhs, const String& rhs ) noexcept;
	bool operator>=( const String& lhs, const char* rhs ) noexcept;
	bool operator>=( const char* lhs, const String& rhs ) noexcept;
} // namespace str_lib

#endif
