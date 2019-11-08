#include <cassert>

#include "common/array.h"
#include "sections/section_bwst.h"

SectionBWST::SectionBWST(std::ifstream &stream, SectionHeader &header) {
    assert(header.version == _supported_version);

    //move to section start
    stream.seekg(header.offset, stream.beg);

    //read array of ::BWSTEntry
    auto array = Array<BWSTEntry>(stream);

    //read strings to ::_data
    size_t data_start = stream.tellg();
    for(const auto& element : array){
        stream.seekg(data_start + element.offset, stream.beg);
        std::vector<uint8_t> data;
        data.resize(element.length);

        _data.emplace(element.id, data);
    }
}

std::vector<uint8_t> SectionBWST::GetString(EntryID id) {
    return _data[id];
}

