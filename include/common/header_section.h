#pragma once

#include <cstdint>

#include "common/fourcc.h"

#pragma pack(push, 1)
struct SectionHeader {
  FourCC magic;
  uint32_t version;
  uint64_t offset;
  uint64_t length;
};
#pragma pack(pop)

static_assert(sizeof(SectionHeader) == 24);
