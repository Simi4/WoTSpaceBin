#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <vector>

template <typename T> 
class Array
{
public:
    explicit Array() = default;

	explicit Array(std::ifstream& stream) {
        /**
        * Size of one element of array
        * This is used as a basic sanity check to make sure data on disk matches expected sizes.
        */
        uint32_t _sizeof_element = 0;
        stream.read(reinterpret_cast<char *>(&_sizeof_element), sizeof(_sizeof_element));
        assert(sizeof(T) == _sizeof_element);

        /**
         * The number of elements in the array.
         */
        uint32_t _element_count = 0;
        stream.read(reinterpret_cast<char *>(&_element_count), sizeof(_element_count));

        for (auto index = 0; index < _element_count; index++) {
            T element{};
            stream.read(reinterpret_cast<char *>(&element), sizeof(element));
            _data.push_back(element);
        }
    }

	size_t size() {
	    return _data.size();
	}

    T& operator[](size_t i) {
        return _data[i];
    }

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }

private:

	/**
	 * Vector of array elements
	 */
    std::vector<T> _data;
};
