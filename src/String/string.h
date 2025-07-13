#ifndef STRING_H
#define STRING_H
#include <cstdlib>
#include <memory.h>
namespace str_lib {

class String {
  char *m_buffer;
  size_t m_capacity;
  size_t m_size;

public:
  String() {
    constexpr size_t BASE_CAPACITY = 16;
    m_buffer = reinterpret_cast<char *>(malloc(BASE_CAPACITY));
    m_capacity = BASE_CAPACITY;
  }
};
} // namespace str_lib
#endif
