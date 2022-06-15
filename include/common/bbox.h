#pragma once

#include "vector3.h"

#pragma pack(push, 1)

/**
 * An axially-aligned bounding-box (AABB).
 */
struct Bbox
{
    /**
     * Bounding box mins
     */
    Vector3 mins{};

    /**
     * Bounding box max
     */
    Vector3 maxs{};
};

#pragma pack(pop)

static_assert(sizeof(Bbox) == 24);