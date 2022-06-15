#pragma once

#include <cstdint>
#include <fstream>

#include "common/array.h"
#include "common/header_section.h"
#include "common/matrix.h"
#include "common/typedefs.h"
#include "common/vector3.h"
#include "sections/section_base.h"

#pragma pack(push, 1)

struct BSMOModelLoddingItem
{
    ListIndex lod_begin = 0;
    ListIndex lod_end = 0;
};
static_assert(sizeof(BSMOModelLoddingItem) == 8);

struct BSMOModelColliderItem
{
    Vector3 collision_bounds_min{};
    Vector3 collision_bounds_max{};
    EntryID bsp_section_name = 0;
    ListIndex bsp_material_kind_begin = 0;
    ListIndex bsp_material_kind_end = 0;
};
static_assert(sizeof(BSMOModelColliderItem) == 36);

struct BSMOBSPMaterialKindItem
{
    ListIndex material_index = 0;
    uint32_t flags = 0; // WorldTriangle::Flags
};
static_assert(sizeof(BSMOBSPMaterialKindItem) == 8);

struct BSMOModelVisibilityItem
{
    Vector3 visibility_bounds_min{};
    Vector3 visibility_bounds_max{};
};
static_assert(sizeof(BSMOModelVisibilityItem) == 24);

struct BSMOLODLoddingItem
{
    float max_distance_sq = 0.0f;
};
static_assert(sizeof(BSMOLODLoddingItem) == 4);

struct BSMOLODRenderItem
{
    ListIndex render_set_begin = 0;
    ListIndex render_set_end = 0;
};
static_assert(sizeof(BSMOLODRenderItem) == 8);

enum BSMORenderFlags : uint32_t
{
    FLAG_NONE = 0,
    FLAG_IS_SKINNED = (1 << 0),
};

struct BSMORenderItem
{
    ListIndex node_begin = 0;
    ListIndex node_end = 0;
    ListIndex material_index = 0;
    ListIndex primitive_index = 0;
    EntryID verts_name = 0;
    EntryID prims_name = 0;
    BSMORenderFlags flags = FLAG_NONE;
};
static_assert(sizeof(BSMORenderItem) == 28);

struct BSMONodeAffectorItem
{
    LocalListIndex local_node_index = 0;
};
static_assert(sizeof(BSMONodeAffectorItem) == 4);

struct BSMOAnimationItem
{
    EntryID anim_name = 0;
    float frame_rate = 0.0f;
    int32_t first_frame = 0;
    int32_t last_Frame = 0;
    EntryID cognate = 0;
    EntryID nodes_name = 0;
    ListIndex channel_node_begin = 0;
    ListIndex channel_node_end = 0;
    EntryID anca_resource_name = 0;
};
static_assert(sizeof(BSMOAnimationItem) == 36);

struct BSMONodeItem
{
    ListIndex parentIndex = 0;
    Matrix initialTransform{};
};
static_assert(sizeof(BSMONodeItem) == 68);

#pragma pack(pop)

class SectionBSMO : public SectionBase
{
  public:
    explicit SectionBSMO(std::ifstream &stream, SectionHeader &header);

    std::span<BSMOModelLoddingItem> GetModelsLoddings();
    std::span<BSMOModelColliderItem> GetModelsColliders();
    std::span<BSMOBSPMaterialKindItem> GetBspMaterialKinds();
    std::span<BSMOModelVisibilityItem> GetModelsVisibilityBounds();
    std::span<BSMOLODRenderItem> GetLodRenders();
    std::span<BSMOLODLoddingItem> GetLodLoddings();
    std::span<BSMORenderItem> GetRenders();
    std::span<BSMONodeAffectorItem> GetNodeAffectors1();
    std::span<BSMOAnimationItem> GetAnimations();
    std::span<BSMONodeAffectorItem> GetNodeAffectors2();
    std::span<BSMONodeItem> GetNodes();

  private:
    static constexpr uint32_t _supported_version = 1;

    std::vector<BSMOModelLoddingItem> _modelsLoddings;
    std::vector<BSMOModelColliderItem> _modelsColliders;
    std::vector<BSMOBSPMaterialKindItem> _bspMaterialKinds;
    std::vector<BSMOModelVisibilityItem> _modelsVisibilityBounds;
    std::vector<BSMOLODLoddingItem> _lodLoddings;
    std::vector<BSMOLODRenderItem> _lodRenders;
    std::vector<BSMORenderItem> _renders;
    std::vector<BSMONodeAffectorItem> _nodeAffectors1;
    std::vector<BSMOAnimationItem> _animations;
    std::vector<BSMONodeAffectorItem> _nodeAffectors2;
    std::vector<BSMONodeItem> _nodes;
};
