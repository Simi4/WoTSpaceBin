#include "sections/section_bsmo.h"

#include <cassert>

SectionBSMO::SectionBSMO(std::ifstream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    _modelsLoddings = read_array<BSMOModelLoddingItem>(stream);
    _modelsColliders = read_array<BSMOModelColliderItem>(stream);
    _bspMaterialKinds = read_array<BSMOBSPMaterialKindItem>(stream);
    _modelsVisibilityBounds = read_array<BSMOModelVisibilityItem>(stream);

    // something messed up starting this line

    //??? just to skip array of 8 bytes elements
    read_array<BSMOLODRenderItem>(stream);

    _lodLoddings = read_array<BSMOLODLoddingItem>(stream);

    //??? just to skip array of 4 bytes elements
    read_array<BSMOLODLoddingItem>(stream);

    _lodRenders = read_array<BSMOLODRenderItem>(stream);
    _renders = read_array<BSMORenderItem>(stream);
    _nodeAffectors1 = read_array<BSMONodeAffectorItem>(stream);
    _animations = read_array<BSMOAnimationItem>(stream);
    _nodeAffectors2 = read_array<BSMONodeAffectorItem>(stream);
    _nodes = read_array<BSMONodeItem>(stream);
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

std::span<BSMONodeAffectorItem> SectionBSMO::GetNodeAffectors1()
{
    return _nodeAffectors1;
}

std::span<BSMOAnimationItem> SectionBSMO::GetAnimations()
{
    return _animations;
}

std::span<BSMONodeAffectorItem> SectionBSMO::GetNodeAffectors2()
{
    return _nodeAffectors2;
}

std::span<BSMONodeItem> SectionBSMO::GetNodes()
{
    return _nodes;
}
