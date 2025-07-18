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

  public:
    String();
    String(const char *cstr);
    String(const String &other);
    String(String &&other);
    String &operator=(const String &);
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
