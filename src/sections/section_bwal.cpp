#include "sections/section_bwal.h"

SectionBWAL::SectionBWAL(std::ifstream &stream, SectionHeader &header) {
    assert(header.version == _supported_version);

    //move to section start
    stream.seekg(header.offset, stream.beg);

    _entries = Array<BWALAssetListEntry>(stream);

    assert(stream.tellg() == header.offset + header.length);
}

Array<BWALAssetListEntry>& SectionBWAL::GetEntries() {
    return _entries;
}
