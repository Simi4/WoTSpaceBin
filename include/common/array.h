#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <span>
#include <vector>

template <typename T> std::vector<T> read_array(std::ifstream &stream)
{
    std::vector<T> result;

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

    // skip array if empty
    if (_element_count == 0)
    {
        return result;
    }

    result.resize(_element_count);
    stream.read(reinterpret_cast<char *>(result.data()), _sizeof_element);
    return result;
}
