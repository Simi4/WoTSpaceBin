#pragma once

#pragma pack(push, 1)

/**
 * A floating point vector of 4 floats.
 */
struct Vector4
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

    /**
     * W component
     */
    float w = 0.0f;
};

#pragma pack(pop)

static_assert(sizeof(Vector4) == 16);
