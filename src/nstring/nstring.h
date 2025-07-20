#ifndef STRING_H
#define STRING_H

#include <stddef.h>

namespace str_lib {

	class String
	{
	public:
		/// ctor
		String();
		/// cstrCtor
		String( const char* cstr );
		/// copyCtor
		String( const String& other );
		/// moveCtor
		String( String&& other ) noexcept;
		/// dtor
		~String();

		/// assignOperators
		String& operator=( const String& rhs );
		String& operator=( String&& rhs ) noexcept;
		String& operator=( const char* cstr );

		/// indexingOperators
		char&       operator[]( size_t index ) { return m_buffer[index]; }
		const char& operator[]( size_t index ) const { return m_buffer[index]; }

		String& operator+=( const String& rhs );

		/// TODO: resize method
		/// TODO: reserve method
		/// TODO: shrink_to_fit method
		/// TODO: begin() end() iterators

		/// return c-style string
		char* cstr() const { return m_buffer; }

		/// return actual String size
		size_t size() const { return m_size; }

		// return actual String capacity
		size_t capacity() const { return m_capacity; }

	private:
		char*  m_buffer;
		size_t m_capacity;
		size_t m_size;

		static constexpr size_t BASE_CAPACITY = 15;
	};
} // namespace str_lib
#endif
