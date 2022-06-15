#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <span>
#include <vector>

static void skip_array(uint32_t size, std::ifstream &stream)
{
    /**
     * Size of one element of array
     * This is used as a basic sanity check to make sure data on disk matches
     * expected sizes.
     */
    uint32_t _sizeof_element = 0;
    stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));

    // check size
    assert(size == _sizeof_element);

    /**
     * The number of elements in the array.
     */
    uint32_t _element_count = 0;
    stream.read(reinterpret_cast<char *>(&_element_count), sizeof(_element_count));

    stream.seekg(_element_count * _sizeof_element, stream.cur);
}

template <typename T> static std::vector<T> read_array(std::ifstream &stream)
{
    /**
     * Size of one element of array
     * This is used as a basic sanity check to make sure data on disk matches
     * expected sizes.
     */
    uint32_t _sizeof_element = 0;
    stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));

    // check size
    assert(sizeof(T) == _sizeof_element);

    /**
     * The number of elements in the array.
     */
    uint32_t _element_count = 0;
    stream.read(reinterpret_cast<char *>(&_element_count), sizeof(_element_count));

    std::vector<T> result(_element_count);
    stream.read(reinterpret_cast<char *>(result.data()), _element_count * _sizeof_element);
    return result;
}
