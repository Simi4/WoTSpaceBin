#include <cassert>

#include "sections/section_bsmo.h"

SectionBSMO::SectionBSMO(std::ifstream &stream, SectionHeader &header) {
    assert(header.version == _supported_version);

    //move to section start
    stream.seekg(header.offset, stream.beg);

    _modelsLoddings = Array<BSMOModelLoddingItem>(stream);
    _modelsColliders = Array<BSMOModelColliderItem>(stream);
    _bspMaterialKinds = Array<BSMOBSPMaterialKindItem>(stream);
    _modelsVisibilityBounds = Array<BSMOModelVisibilityItem>(stream);

    //something messed up starting this line

    Array<BSMOLODRenderItem> temp1(stream); //??? just to skip array of 8 bytes elements

    _lodLoddings = Array<BSMOLODLoddingItem>(stream);

    Array<BSMOLODLoddingItem> temp2(stream); //??? just to skip array of 4 bytes elements

    _lodRenders = Array<BSMOLODRenderItem>(stream);
    _renders = Array<BSMORenderItem>(stream);
    _nodeAffectors1 = Array<BSMONodeAffectorItem>(stream);
    _animations = Array<BSMOAnimationItem>(stream);
    _nodeAffectors2 = Array<BSMONodeAffectorItem>(stream);
    _nodes = Array<BSMONodeItem>(stream);
}

Array<BSMOModelLoddingItem>& SectionBSMO::GetModelsLoddings() {
    return _modelsLoddings;
}

Array<BSMOModelColliderItem>& SectionBSMO::GetModelsColliders() {
    return _modelsColliders;
}

Array<BSMOBSPMaterialKindItem>& SectionBSMO::GetBspMaterialKinds() {
    return _bspMaterialKinds;
}

Array<BSMOModelVisibilityItem>& SectionBSMO::GetModelsVisibilityBounds() {
    return _modelsVisibilityBounds;
}

Array<BSMOLODLoddingItem>& SectionBSMO::GetLodLoddings() {
    return _lodLoddings;
}

Array<BSMOLODRenderItem>& SectionBSMO::GetLodRenders() {
    return _lodRenders;
}

Array<BSMORenderItem>& SectionBSMO::GetRenders() {
    return _renders;
}

Array<BSMONodeAffectorItem>& SectionBSMO::GetNodeAffectors1() {
    return _nodeAffectors1;
}

Array<BSMOAnimationItem>& SectionBSMO::GetAnimations() {
    return _animations;
}

Array<BSMONodeAffectorItem>& SectionBSMO::GetNodeAffectors2() {
    return _nodeAffectors2;
}

Array<BSMONodeItem> &SectionBSMO::GetNodes() {
    return _nodes;
}
