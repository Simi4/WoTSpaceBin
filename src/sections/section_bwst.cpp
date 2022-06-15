#include "sections/section_bwst.h"

#include <cassert>

#include "common/array.h"

SectionBWST::SectionBWST(std::ifstream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    // read array of ::BWSTEntry
    auto array = read_array<BWSTEntry>(stream);

    // read strings to ::_data
    size_t data_start = stream.tellg();
    for (const auto &element : array)
    {
        std::string data;
        data.resize(element.length);

        stream.seekg(data_start + element.offset, stream.beg);
        stream.read(reinterpret_cast<char *>(data.data()), element.length);

        _data.emplace(element.id, data);
    }
}

std::string_view SectionBWST::GetString(EntryID id)
{
    return _data[id];
}
