#include "sections/section_bsma.h"

#include <cassert>

SectionBSMA::SectionBSMA(std::istream &stream, SectionHeader &header)
{
    assert(header.version == _supported_version);

    // move to section start
    stream.seekg(header.offset, stream.beg);

    _materials = read_array<BSMAMaterialItem>(stream);
    _effects = read_array<BSMAEffectItem>(stream);
    _shaderProperties = read_array<BSMAShaderPropertyItem>(stream);
    _shaderPropertiesMatrix = read_array<BSMAShaderPropertyMatrixItem>(stream);
    _shaderPropertiesVectors = read_array<BSMAShaderPropertyVectorItem>(stream);

    // TODO: textures

    // assert(stream.tellg() == header.offset + header.length);
}

std::span<BSMAMaterialItem> SectionBSMA::GetMaterials()
{
    return _materials;
}

std::span<BSMAEffectItem> SectionBSMA::GetEffects()
{
    return _effects;
}

std::span<BSMAShaderPropertyItem> SectionBSMA::GetShaderProperties()
{
    return _shaderProperties;
}

std::span<BSMAShaderPropertyMatrixItem> SectionBSMA::GetShaderPropertiesMatrix()
{
    return _shaderPropertiesMatrix;
}

std::span<BSMAShaderPropertyVectorItem> SectionBSMA::GetShaderPropertiesVectors()
{
    return _shaderPropertiesVectors;
}
