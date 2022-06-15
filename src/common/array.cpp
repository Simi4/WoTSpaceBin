#include "common/array.h"

namespace utils
{

void skip_single_element(uint32_t size, std::istream &stream)
{
    uint32_t _sizeof_element = 0;
    stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));

    // check size
    assert(size == _sizeof_element);

    stream.seekg(_sizeof_element, stream.cur);
}

void skip_array(uint32_t size, std::istream &stream)
{
    uint32_t _sizeof_element = 0;
    stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));

    // check size
    assert(size == _sizeof_element);

    uint32_t _element_count = 0;
    stream.read(reinterpret_cast<char *>(&_element_count), sizeof(_element_count));

    stream.seekg(_element_count * _sizeof_element, stream.cur);
}

} // namespace utils