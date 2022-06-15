#pragma once

#include <cstdint>

#include "common/fourcc.h"

#pragma pack(push, 1)
struct FileHeader
{
    FourCC magic{};
    uint32_t version = 0;
    uint32_t header_size = 0;
    uint64_t file_size = 0;
    uint32_t num_sections = 0;
};
#pragma pack(pop)

static_assert(sizeof(FileHeader) == 24);
