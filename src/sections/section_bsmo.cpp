#include "sections/section_bsmo.h"

#include <cassert>

SectionBSMO::SectionBSMO(std::istream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    _modelsLoddings = utils::read_array<BSMOModelLoddingItem>(stream);

    utils::skip_array(4, stream);

    _modelsColliders = utils::read_array<BSMOModelColliderItem>(stream);
    _bspMaterialKinds = utils::read_array<BSMOBSPMaterialKindItem>(stream);
    _modelsVisibilityBounds = utils::read_array<BSMOModelVisibilityItem>(stream);

    utils::skip_array(8, stream);
    utils::skip_array(4, stream);

    _lodLoddings = utils::read_array<BSMOLODLoddingItem>(stream);
    _lodRenders = utils::read_array<BSMOLODRenderItem>(stream);
    _renders = utils::read_array<BSMORenderItem>(stream);

    utils::skip_array(4, stream);
    utils::skip_array(72, stream);
    utils::skip_array(64, stream);
    utils::skip_array(48, stream);
    utils::skip_array(40, stream);
    utils::skip_array(8, stream);
    utils::skip_array(8, stream);
    utils::skip_array(8, stream);

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
