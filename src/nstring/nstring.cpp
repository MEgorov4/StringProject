#include "nstring.h"
#include <cstdlib>
#include <cstring>

using namespace str_lib;

String::String()
{
    const size_t BASE_CAPACITY = 16;
    m_buffer = reinterpret_cast<char *>(malloc(BASE_CAPACITY));
    m_capacity = BASE_CAPACITY - 1;
    m_size = 0;
    m_buffer[m_size] = '\0';
}

String::String(const char *cstr)
{
    m_size = strlen(cstr);
    m_capacity = m_size;
    m_buffer = reinterpret_cast<char *>(malloc(m_capacity + 1));
    memcpy(m_buffer, cstr, m_size);
    m_buffer[m_size] = '\0';
};

String::String(const String &other)
{
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    m_buffer = reinterpret_cast<char *>(malloc(m_capacity + 1));
    memcpy(m_buffer, other.m_buffer, m_size);
    m_buffer[m_size] = '\0';
}

String::String(String &&other)
{
    m_buffer = other.m_buffer;
    m_capacity = other.m_capacity;
    m_size = other.m_size;

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
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_buffer = rhs.m_buffer;

        rhs.m_buffer = nullptr;
    }
    return *this;
};
