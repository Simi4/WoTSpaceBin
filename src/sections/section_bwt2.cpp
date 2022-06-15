#include "sections/section_bwt2.h"

#include <cassert>

#include "common/array.h"

SectionBWT2::SectionBWT2(std::istream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    utils::skip_single_element(32, stream);
    utils::skip_array(8, stream);
    utils::skip_array(4, stream);
    utils::skip_single_element(128, stream);
    utils::skip_array(4, stream);
    utils::skip_array(8, stream);
    utils::skip_array(40, stream);
    utils::skip_array(4, stream);

    assert(stream.tellg() == header.offset + header.length);
}
