#pragma once

#include <cstdint>
#include <fstream>

#include "common/bbox.h"
#include "common/matrix.h"
#include "common/header_section.h"
#include "common/vector4.h"
#include "sections/section_base.h"
#include "sections/section_bwst.h"

typedef uint32_t ListIndex;

#pragma pack(push, 1)

/**
 * Contains the information representing a material, including effect and properties to set.
 */
struct BSMAMaterialItem
{
    ListIndex effectIndex = 0;
    ListIndex shaderPropertyBegin = 0;
    ListIndex shaderPropertyEnd = 0;
    uint32_t unknown = 0;
};
static_assert(sizeof(BSMAMaterialItem) == 16);


/**
 * Contains the shader file name to use.
 */
struct BSMAEffectItem
{
    EntryID effectName;
};
static_assert(sizeof(BSMAEffectItem) == 4);

/**
 * Contains the information on a shader property, including name and value.
 */
struct BSMAShaderPropertyItem
{
    EntryID propertyName;
    uint32_t type; //ShaderPropertyItem::Type
    union
    {
        float floatProp;
        int32_t intProp;
        int32_t index;
        EntryID stringEntry; //BaseTex
    } property;
};
static_assert(sizeof(BSMAShaderPropertyItem) == 12);

/**
 * Contains the matrix for a shader property so it only needs to be referenced by index.
 */
struct BSMAShaderPropertyMatrixItem
{
    Matrix matrix;
};
static_assert(sizeof(BSMAShaderPropertyMatrixItem) == 64);

/**
 * Contains the vector data for a shader property so it only needs to be referenced by index.
 */
struct BSMAShaderPropertyVectorItem
{
    Vector4 vector;
};
static_assert(sizeof(BSMAShaderPropertyVectorItem) == 16);

#pragma pack(pop)

/**
 * BigWorld Base Materials
 */
class SectionBSMA : public SectionBase {
public:
    explicit SectionBSMA(std::ifstream& stream, SectionHeader& header);

    Array<BSMAMaterialItem>& GetMaterials();
    Array<BSMAEffectItem>& GetEffects();
    Array<BSMAShaderPropertyItem>& GetShaderProperties();
    Array<BSMAShaderPropertyMatrixItem>& GetShaderPropertiesMatrix();
    Array<BSMAShaderPropertyVectorItem>& GetShaderPropertiesVectors();

private:
    static constexpr uint32_t _supported_version = 1;

    /**
     * Contains the information representing a material, including effect and properties to set.
     */
    Array<BSMAMaterialItem> _materials;

    /**
     * Contains the shader file name to use.
     */
    Array<BSMAEffectItem> _effects;

    /**
     * Contains the information on a shader property, including name and value.
     */
    Array<BSMAShaderPropertyItem> _shaderProperties;

    /**
     * Contains the matrix for a shader property so it only needs to be referenced by index.
     */
    Array<BSMAShaderPropertyMatrixItem> _shaderPropertiesMatrix;

    /**
     * Contains the vector data for a shader property so it only needs to be referenced by index.
     */
    Array<BSMAShaderPropertyVectorItem> _shaderPropertiesVectors;

};
