#pragma once

#pragma pack(push, 1)

/**
 * A floating point vector of 3 floats.
 */
struct Vector3
{
    /**
     * X component
     */
    float x = 0.0f;

    /**
     * Y component
     */
    float y = 0.0f;

    /**
     * Z component
     */
    float z = 0.0f;
};

#pragma pack(pop)

static_assert(sizeof(Vector3) == 12);
