#include <cassert>

#include "sections/section_bsma.h"

SectionBSMA::SectionBSMA(std::ifstream &stream, SectionHeader &header) {
    assert(header.version == _supported_version);

    //move to section start
    stream.seekg(header.offset, stream.beg);

    _materials = Array<BSMAMaterialItem>(stream, true);
    _effects = Array<BSMAEffectItem>(stream);
    _shaderProperties =  Array<BSMAShaderPropertyItem>(stream);
    _shaderPropertiesMatrix = Array<BSMAShaderPropertyMatrixItem>(stream);
    _shaderPropertiesVectors = Array<BSMAShaderPropertyVectorItem>(stream);

    assert(stream.tellg() == header.offset + header.length);
}

Array<BSMAMaterialItem>& SectionBSMA::GetMaterials() {
    return _materials;
}

Array<BSMAEffectItem>& SectionBSMA::GetEffects() {
    return _effects;
}

Array<BSMAShaderPropertyItem>& SectionBSMA::GetShaderProperties() {
    return _shaderProperties;
}

Array<BSMAShaderPropertyMatrixItem>& SectionBSMA::GetShaderPropertiesMatrix() {
    return _shaderPropertiesMatrix;
}

Array<BSMAShaderPropertyVectorItem>& SectionBSMA::GetShaderPropertiesVectors() {
    return _shaderPropertiesVectors;
}
