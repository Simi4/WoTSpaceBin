#include <cassert>

#include "sections/section_wgsd.h"

SectionWGSD::SectionWGSD(std::ifstream &stream, SectionHeader &header) {
    assert(header.version == _supported_version);

    //move to section start
    stream.seekg(header.offset, stream.beg);

    _decalEntries = Array<WGSDDecal>(stream);
}

Array<WGSDDecal> &SectionWGSD::GetDecalEntries() {
    return _decalEntries;
}
