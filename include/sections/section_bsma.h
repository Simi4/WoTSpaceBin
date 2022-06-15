#pragma once

#include <cstdint>
#include <fstream>

#include "common/bbox.h"
#include "common/header_section.h"
#include "common/matrix.h"
#include "common/vector4.h"
#include "sections/section_base.h"
#include "sections/section_bwst.h"

#pragma pack(push, 1)

struct BSMAMaterialItem
{
    ListIndex effectIndex = 0;
    ListIndex shaderPropertyBegin = 0;
    ListIndex shaderPropertyEnd = 0;
    uint32_t unknown = 0;
};
static_assert(sizeof(BSMAMaterialItem) == 16);

struct BSMAEffectItem
{
    EntryID effectName;
};
static_assert(sizeof(BSMAEffectItem) == 4);

struct BSMAShaderPropertyItem
{
    EntryID propertyName;
    uint32_t type; // ShaderPropertyItem::Type
    union {
        float floatProp;
        int32_t intProp;
        int32_t index;
        EntryID stringEntry; // BaseTex
    } property;
};
static_assert(sizeof(BSMAShaderPropertyItem) == 12);

struct BSMAShaderPropertyMatrixItem
{
    Matrix matrix;
};
static_assert(sizeof(BSMAShaderPropertyMatrixItem) == 64);

struct BSMAShaderPropertyVectorItem
{
    Vector4 vector;
};
static_assert(sizeof(BSMAShaderPropertyVectorItem) == 16);

#pragma pack(pop)

class SectionBSMA : public SectionBase
{
  public:
    explicit SectionBSMA(std::ifstream &stream, SectionHeader &header);

    std::span<BSMAMaterialItem> GetMaterials();
    std::span<BSMAEffectItem> GetEffects();
    std::span<BSMAShaderPropertyItem> GetShaderProperties();
    std::span<BSMAShaderPropertyMatrixItem> GetShaderPropertiesMatrix();
    std::span<BSMAShaderPropertyVectorItem> GetShaderPropertiesVectors();

  private:
    static constexpr uint32_t _supported_version = 1;

    std::vector<BSMAMaterialItem> _materials;
    std::vector<BSMAEffectItem> _effects;
    std::vector<BSMAShaderPropertyItem> _shaderProperties;
    std::vector<BSMAShaderPropertyMatrixItem> _shaderPropertiesMatrix;
    std::vector<BSMAShaderPropertyVectorItem> _shaderPropertiesVectors;
};
