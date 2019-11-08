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

/**
 * Contains the list of LODs for this model.
 */
struct BSMOModelLoddingItem
{
    ListIndex lod_begin = 0;
    ListIndex lod_end = 0;
};
static_assert(sizeof(BSMOModelLoddingItem) == 8);

/**
 * Contains the collision data for this model such as bounds and bsp.
 */
struct BSMOModelColliderItem
{
    Vector3 collision_bounds_min{};
    Vector3 collision_bounds_max{};
    EntryID bsp_section_name = 0;
    ListIndex bsp_material_kind_begin = 0;
    ListIndex bsp_material_kind_end = 0;
};
static_assert(sizeof(BSMOModelColliderItem) == 36);

/**
 * Contains data for bsp material linkage and flags
 */
struct BSMOBSPMaterialKindItem
{
    ListIndex material_index = 0;
    uint32_t flags = 0; //WorldTriangle::Flags
};
static_assert(sizeof(BSMOBSPMaterialKindItem) == 8);

/**
 * Contains the visibility bounds for the model
 */
struct BSMOModelVisibilityItem
{
    Vector3 visibility_bounds_min{};
    Vector3 visibility_bounds_max{};
};
static_assert(sizeof(BSMOModelVisibilityItem) == 24);

/**
 * Contains the distance information for the lod.
 */
struct BSMOLODLoddingItem
{
    float max_distance_sq = 0.0f;
};
static_assert(sizeof(BSMOLODLoddingItem) == 4);

/**
 * Contains the render sets to draw for this lod
 */
struct BSMOLODRenderItem
{
    ListIndex render_set_begin = 0;
    ListIndex render_set_end = 0;
};
static_assert(sizeof(BSMOLODRenderItem) == 8);

enum BSMORenderFlags : uint32_t
{
    FLAG_NONE       = 0,
    FLAG_IS_SKINNED = (1<<0),
};

/**
 * Contains the data for rendering a model segment, including nodes, material, primitives, verts and draw flags.
 */
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

/**
 * Contains a relative index to a nodes
 */
struct BSMONodeAffectorItem
{
    LocalListIndex local_node_index = 0;
};
static_assert(sizeof(BSMONodeAffectorItem) == 4);

/**
 * Contains information for animating a model including the animation name, frames, nodes and channels.
 */
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

/**
 * Contains the immutable data to represent a node, including a parent relative offset and initial transform.
 */
struct BSMONodeItem
{
    ListIndex parentIndex = 0;
    Matrix initialTransform{};
};
static_assert(sizeof(BSMONodeItem) == 68);


#pragma pack(pop)

/**
 * BigWorld Base Models
 *
 */
class SectionBSMO : public SectionBase {
public:
    explicit SectionBSMO(std::ifstream& stream, SectionHeader& header);

    /**
     * Contains the list of LODs for this model.
     */
    Array<BSMOModelLoddingItem>& GetModelsLoddings();

    /**
     * Contains the collision data for this model such as bounds and bsp.
     */
    Array<BSMOModelColliderItem>& GetModelsColliders();

    /**
     * Contains data for bsp material linkage and flags
     */
    Array<BSMOBSPMaterialKindItem>& GetBspMaterialKinds();

    /**
    * Contains the visibility bounds for the model.
    */
    Array<BSMOModelVisibilityItem>& GetModelsVisibilityBounds();

    /**
     * Contains the render sets to draw for this lod.
     */
    Array<BSMOLODRenderItem>& GetLodRenders();

    /**
     * Contains the distance information for the lod.
     */
    Array<BSMOLODLoddingItem>& GetLodLoddings();

    /**
     * Contains the data for rendering a model segment, including nodes, material, primitives, verts and draw flags.
     */
    Array<BSMORenderItem>& GetRenders();

    /**
     * Contains a relative index to a node that affects this render set, so we can have sequential access.
     */
    Array<BSMONodeAffectorItem>& GetNodeAffectors1();

    /**
     * Contains information for animating a model including the animation name, frames, nodes and channels.
     */
    Array<BSMOAnimationItem>& GetAnimations();

    /**
     * Contains an index to the nodes that the animation effects so they can be stored sequentially.
     */
    Array<BSMONodeAffectorItem>& GetNodeAffectors2();

    /**
     * Contains an index to the nodes that the animation effects so they can be stored sequentially.
     */
    Array<BSMONodeItem>& GetNodes();

private:
    static constexpr uint32_t _supported_version = 1;

    /**
     * Contains the list of LODs for this model.
     */
    Array<BSMOModelLoddingItem> _modelsLoddings;

    /**
     * Contains the collision data for this model such as bounds and bsp.
     */
    Array<BSMOModelColliderItem> _modelsColliders;

    /**
     * Contains data for bsp material linkage and flags
     */
    Array<BSMOBSPMaterialKindItem> _bspMaterialKinds;

    /**
     * Contains the visibility bounds for the model.
     */
    Array<BSMOModelVisibilityItem> _modelsVisibilityBounds;

    /**
     * Contains the distance information for the lod.
     */
    Array<BSMOLODLoddingItem> _lodLoddings;

    /**
     * Contains the render sets to draw for this lod.
     */
    Array<BSMOLODRenderItem> _lodRenders;

    /**
     * Contains the data for rendering a model segment, including nodes, material, primitives, verts and draw flags.
     */
    Array<BSMORenderItem> _renders;

    /**
     * Contains a relative index to a node that affects this render set, so we can have sequential access.
     */
    Array<BSMONodeAffectorItem> _nodeAffectors1;

    /**
     * Contains information for animating a model including the animation name, frames, nodes and channels.
     */
    Array<BSMOAnimationItem> _animations;

    /**
     * Contains an index to the nodes that the animation effects so they can be stored sequentially.
     */
    Array<BSMONodeAffectorItem> _nodeAffectors2;

    /**
     * Contains an index to the nodes that the animation effects so they can be stored sequentially.
     */
    Array<BSMONodeItem> _nodes;

};
