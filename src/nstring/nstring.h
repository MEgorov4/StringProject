#ifndef NSTRING_H
#define NSTRING_H

#include <cstdint>
#include <limits>
#include <istream>
#include <ostream>

namespace nstring {

	class String
	{
	public:
		/// ctors/dtor
		String();
		explicit String(size_t count, char c);
		String(const char* cstr);
		String(const String& rhs);
		String(String&& rhs) noexcept;
		~String() noexcept;

		/// assignment
		String& operator=(const String& rhs);
		String& operator=(String&& rhs) noexcept;
		String& operator=(const char* cstr);

		/// access
		char& operator[](size_t index) noexcept { return m_buffer[index]; }
		const char& operator[](size_t index) const noexcept { return m_buffer[index]; }

		char& at(size_t index);
		const char& at(size_t index) const;

		char* begin() noexcept { return m_buffer; }
		const char* begin() const noexcept { return m_buffer; }

		char* end() noexcept { return m_buffer + m_size; }
		const char* end() const noexcept { return m_buffer + m_size; }

		const char* cstr() const noexcept { return m_buffer; }
		size_t size() const noexcept { return m_size; }
		size_t capacity() const noexcept { return m_capacity; }

		bool empty() const noexcept { return m_size == 0; }

		/// modifiers
		String& operator+=(const String& rhs);
		String& operator+=(const char* rhs);

		void swap(String& other) noexcept;
		friend void swap(String& left, String& right) noexcept;

		void clear();
		void resize(size_t size, char ch = '\0');
		void reserve(size_t capacity);
		void shrink_to_fit();
		void push_back(char ch);

		/// constants
		static constexpr size_t BASE_CAPACITY = 15;
		static constexpr size_t GROW_COEF = 2;
		static constexpr size_t MAX_CAPACITY = std::numeric_limits<size_t>().max() / 4;

	private:
		/// ensures buffer capacity is enough for newSize.
		/// reallocates m_buffer and updates m_capacity if needed.
		void ensure_capacity(size_t newSize);

	private:
		char* m_buffer;
		size_t m_capacity;
		size_t m_size;
	};

	/// non-member functions and operators
	void swap(String& left, String& right) noexcept;

	std::istream& operator>>(std::istream& in, String& rhs);
	std::ostream& operator<<(std::ostream& stream, const String& rhs) noexcept;

	String operator+(const String& lhs, const String& rhs);
	String operator+(const String& lhs, const char* rhs);
	String operator+(const char* lhs, const String& rhs);

	bool operator==(const String& lhs, const String& rhs) noexcept;
	bool operator==(const String& lhs, const char* rhs) noexcept;
	bool operator==(const char* lhs, const String& rhs) noexcept;

	bool operator!=(const String& lhs, const String& rhs) noexcept;
	bool operator!=(const String& lhs, const char* rhs) noexcept;
	bool operator!=(const char* lhs, const String& rhs) noexcept;

	bool operator<(const String& lhs, const String& rhs) noexcept;
	bool operator<(const String& lhs, const char* rhs) noexcept;
	bool operator<(const char* lhs, const String& rhs) noexcept;

	bool operator<=(const String& lhs, const String& rhs) noexcept;
	bool operator<=(const String& lhs, const char* rhs) noexcept;
	bool operator<=(const char* lhs, const String& rhs) noexcept;

	bool operator>(const String& lhs, const String& rhs) noexcept;
	bool operator>(const String& lhs, const char* rhs) noexcept;
	bool operator>(const char* lhs, const String& rhs) noexcept;

	bool operator>=(const String& lhs, const String& rhs) noexcept;
	bool operator>=(const String& lhs, const char* rhs) noexcept;
	bool operator>=(const char* lhs, const String& rhs) noexcept;
}  // namespace nstring

#endif
