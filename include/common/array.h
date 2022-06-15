#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <span>
#include <vector>

namespace utils
{

void skip_single_element(uint32_t size, std::istream &stream);

void skip_array(uint32_t size, std::istream &stream);

template <typename T> std::vector<T> read_array(std::istream &stream)
{
    uint32_t _sizeof_element = 0;
    stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));

    // check size
    assert(sizeof(T) == _sizeof_element);

    uint32_t _element_count = 0;
    stream.read(reinterpret_cast<char *>(&_element_count), sizeof(_element_count));

    std::vector<T> result(_element_count);
    stream.read(reinterpret_cast<char *>(result.data()), _element_count * _sizeof_element);
    return result;
}

} // namespace utils
