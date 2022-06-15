#pragma once

#include <cstdint>
#include <istream>

#include "common/array.h"
#include "common/header_section.h"
#include "common/matrix.h"
#include "common/typedefs.h"
#include "common/vector3.h"
#include "sections/section_base.h"

#pragma pack(push, 1)

struct BSMOModelLoddingItem
{
    ListIndex lod_begin;
    ListIndex lod_end;
};
static_assert(sizeof(BSMOModelLoddingItem) == 8);

struct BSMOModelColliderItem
{
    Vector3 collision_bounds_min;
    Vector3 collision_bounds_max;
    EntryID bsp_section_name;
    ListIndex bsp_material_kind_begin;
    ListIndex bsp_material_kind_end;
};
static_assert(sizeof(BSMOModelColliderItem) == 36);

struct BSMOBSPMaterialKindItem
{
    ListIndex material_index;
    uint32_t flags; // WorldTriangle::Flags
};
static_assert(sizeof(BSMOBSPMaterialKindItem) == 8);

struct BSMOModelVisibilityItem
{
    Vector3 visibility_bounds_min;
    Vector3 visibility_bounds_max;
};
static_assert(sizeof(BSMOModelVisibilityItem) == 24);

struct BSMOLODLoddingItem
{
    float max_distance_sq;
};
static_assert(sizeof(BSMOLODLoddingItem) == 4);

struct BSMOLODRenderItem
{
    ListIndex render_set_begin;
    ListIndex render_set_end;
};
static_assert(sizeof(BSMOLODRenderItem) == 8);

enum BSMORenderFlags : uint32_t
{
    FLAG_NONE = 0,
    FLAG_IS_SKINNED = (1 << 0),
};

struct BSMORenderItem
{
    ListIndex node_begin;
    ListIndex node_end;
    ListIndex material_index;
    ListIndex primitive_index;
    EntryID verts_name;
    EntryID prims_name;
    BSMORenderFlags flags;
};
static_assert(sizeof(BSMORenderItem) == 28);

#pragma pack(pop)

class SectionBSMO : public SectionBase
{
  public:
    explicit SectionBSMO(std::istream &stream, SectionHeader &header);

    std::span<BSMOModelLoddingItem> GetModelsLoddings();
    std::span<BSMOModelColliderItem> GetModelsColliders();
    std::span<BSMOBSPMaterialKindItem> GetBspMaterialKinds();
    std::span<BSMOModelVisibilityItem> GetModelsVisibilityBounds();
    std::span<BSMOLODRenderItem> GetLodRenders();
    std::span<BSMOLODLoddingItem> GetLodLoddings();
    std::span<BSMORenderItem> GetRenders();

  private:
    static constexpr uint32_t _supported_version = 3;

    std::vector<BSMOModelLoddingItem> _modelsLoddings;
    std::vector<BSMOModelColliderItem> _modelsColliders;
    std::vector<BSMOBSPMaterialKindItem> _bspMaterialKinds;
    std::vector<BSMOModelVisibilityItem> _modelsVisibilityBounds;
    std::vector<BSMOLODLoddingItem> _lodLoddings;
    std::vector<BSMOLODRenderItem> _lodRenders;
    std::vector<BSMORenderItem> _renders;
};
