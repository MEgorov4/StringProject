#include "nstring.h"
#include <cstdlib>
#include <cstring>

using namespace str_lib;

String::String() : m_capacity(BASE_CAPACITY - 1), m_size(0)
{
    // Alloc [data-15b][null-term-1b]
    m_buffer = reinterpret_cast<char *>(malloc(m_capacity + 1));
    // Place null-term in first place
    m_buffer[m_size] = '\0';
}

String::String(const char *cstr) : m_capacity(strlen(cstr)), m_size(m_capacity)
{
    // Alloc [strlen(cstr)][null-term-1b]
    m_buffer = reinterpret_cast<char *>(malloc(m_capacity + 1));
    // Copy data from cstr [strlen(cstr)] -> [m_buffer.size()][m_capacity - size][null-term]
    memcpy(m_buffer, cstr, m_size);
    // Place null-term in last place
    m_buffer[m_size] = '\0';
};

String::String(const String &other) : String(other.cstr())
{
    // Delligate to fromCSTR constructor
}

String::String(String &&other)
{
    // Bagage all data from r-value obj
    m_buffer = other.m_buffer;
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    // Cearfuly kill r-value`s data-pointer
    other.m_buffer = nullptr;
};

String::~String()
{
    free(m_buffer);
}

String &String::operator=(const String &rhs)
{
    if (&rhs != this)
    {
        free(m_buffer);
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_buffer = reinterpret_cast<char *>(malloc(m_capacity + 1));
        memcpy(m_buffer, rhs.m_buffer, m_size);
        m_buffer[m_size] = '\0';
    }
    return *this;
};

String &String::operator=(String &&rhs)
{
    if (&rhs != this)
    {
        free(m_buffer);
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_buffer = rhs.m_buffer;

        rhs.m_buffer = nullptr;
    }
    return *this;
};
str_lib::String &str_lib::String::operator=(const char *cstr)
{
    String newString(cstr);

    free(m_buffer);
    m_buffer = newString.m_buffer;
    m_capacity = newString.capacity();
    m_size = newString.size();

    newString.m_buffer = nullptr;

    return *this;
};
