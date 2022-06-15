#include "sections/section_bsmo.h"

#include <cassert>

SectionBSMO::SectionBSMO(std::istream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    _modelsLoddings = read_array<BSMOModelLoddingItem>(stream);

    skip_array(4, stream);

    _modelsColliders = read_array<BSMOModelColliderItem>(stream);
    _bspMaterialKinds = read_array<BSMOBSPMaterialKindItem>(stream);
    _modelsVisibilityBounds = read_array<BSMOModelVisibilityItem>(stream);

    skip_array(8, stream);
    skip_array(4, stream);

    _lodLoddings = read_array<BSMOLODLoddingItem>(stream);
    _lodRenders = read_array<BSMOLODRenderItem>(stream);
    _renders = read_array<BSMORenderItem>(stream);

    skip_array(4, stream);
    skip_array(72, stream);
    skip_array(64, stream);
    skip_array(48, stream);
    skip_array(40, stream);
    skip_array(8, stream);
    skip_array(8, stream);
    skip_array(8, stream);

    assert(stream.tellg() == header.offset + header.length);
}

std::span<BSMOModelLoddingItem> SectionBSMO::GetModelsLoddings()
{
    return _modelsLoddings;
}

std::span<BSMOModelColliderItem> SectionBSMO::GetModelsColliders()
{
    return _modelsColliders;
}

std::span<BSMOBSPMaterialKindItem> SectionBSMO::GetBspMaterialKinds()
{
    return _bspMaterialKinds;
}

std::span<BSMOModelVisibilityItem> SectionBSMO::GetModelsVisibilityBounds()
{
    return _modelsVisibilityBounds;
}

std::span<BSMOLODLoddingItem> SectionBSMO::GetLodLoddings()
{
    return _lodLoddings;
}

std::span<BSMOLODRenderItem> SectionBSMO::GetLodRenders()
{
    return _lodRenders;
}

std::span<BSMORenderItem> SectionBSMO::GetRenders()
{
    return _renders;
}
