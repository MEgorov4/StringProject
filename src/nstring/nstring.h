#ifndef STRING_H
#define STRING_H

#include <stddef.h>

namespace str_lib {

	class String
	{
	public:
		/// ctor
		String();
		/// ctor
		explicit String( size_t count, char c );
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

		/// appendOperator
		/// TODO: add r-value appendOperator
		String& operator+=( const String& rhs );

		/// random access iterators
		char*       begin() noexcept { return m_buffer; }
		const char* begin() const noexcept { return m_buffer; }
		char*       end() noexcept { return m_buffer + m_size; }
		const char* end() const noexcept { return m_buffer + m_size; }

		/// getters TODO: think about naming
		char*  cstr() const { return m_buffer; }
		size_t size() const { return m_size; }
		size_t capacity() const { return m_capacity; }

		/// setters TODO: think about naming
		void resize( size_t size, char ch = '\0' );
		void reserve( size_t capacity );
		void shrink_to_fit();

	private:
		void ensure_capacity( size_t size );

	private:
		char*  m_buffer;
		size_t m_capacity;
		size_t m_size;

		static constexpr size_t BASE_CAPACITY = 15;
		static constexpr size_t GROW_COEF     = 2;
	};

	String operator+( const String& lhs, const String& rhs );
	String operator+( const String& lhs, const char* rhs );
	String operator+( const char* lhs, const String& rhs );
} // namespace str_lib
#endif
