#ifndef STRING_H
#define STRING_H

#include <stddef.h>

namespace str_lib
{

class String
{
    char *m_buffer;
    size_t m_capacity;
    size_t m_size;

    static constexpr size_t BASE_CAPACITY = 16;
    static constexpr size_t EXTRA_CAPACITY = 8;

  public:
    String();
    String(const char *cstr);
    String(const String &other);
    String(String &&other);
    String &operator=(const String &);
    String &operator=(const char *cstr);
    String &operator=(String &&);
    ~String();

    size_t size() const
    {
        return m_size;
    }
    size_t capacity() const
    {
        return m_capacity;
    }
    char *cstr() const
    {
        return m_buffer;
    }
};
} // namespace str_lib
#endif
