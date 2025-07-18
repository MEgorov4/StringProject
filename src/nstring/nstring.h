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
    String(const String &other);
    String(String &&other);
    String &operator=(const String &);
    String &operator=(String &&);
    ~String();
};
} // namespace str_lib
#endif
