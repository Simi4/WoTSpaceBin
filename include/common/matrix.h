#pragma once

#pragma pack(push, 1)

/**
 * A 4x4 matrix, in row major format.
 */
struct Matrix
{
    union {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
};

#pragma pack(pop)

static_assert(sizeof(Matrix) == 64);
