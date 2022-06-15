#include "sections/section_bsmi.h"

#include <cassert>

SectionBSMI::SectionBSMI(std::istream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    _transforms = read_array<Matrix>(stream);
    _chunkModels = read_array<BSMIChunkModel>(stream);
    _visibilityMasks = read_array<uint32_t>(stream);
    _modelIds = read_array<BSMIModelId>(stream);

    // TODO

    // assert(stream.tellg() == header.offset + header.length);
}

std::span<Matrix> SectionBSMI::GetTransforms()
{
    return _transforms;
}

std::span<BSMIChunkModel> SectionBSMI::GetChunkModels()
{
    return _chunkModels;
}

std::span<uint32_t> SectionBSMI::GetVisibilityMasks()
{
    return _visibilityMasks;
}

std::span<BSMIModelId> SectionBSMI::GetModelIds()
{
    return _modelIds;
}
