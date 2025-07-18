#include "nstring.h"
#include <cstdlib>
#include <cstring>

using namespace str_lib;

String::String()
{
    constexpr size_t BASE_CAPACITY = 16;
    m_buffer = reinterpret_cast<char *>(malloc(BASE_CAPACITY));
    m_capacity = BASE_CAPACITY;
    m_size = 0;
}

String::String(const String &other)
{
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    m_buffer = reinterpret_cast<char *>(malloc(m_capacity));
    memcpy(m_buffer, other.m_buffer, m_capacity);
};

String::String(String &&other)
{
    m_buffer = other.m_buffer;
    m_capacity = other.m_capacity;
    m_size = other.m_size;
};

String::~String()
{
    free(m_buffer);
}

String &str_lib::String::operator=(const String &other)
{
    return *this;
};

String &str_lib::String::operator=(String &&)
{
    return *this;
};
