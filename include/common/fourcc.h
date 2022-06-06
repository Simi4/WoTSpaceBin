#pragma once

#include <cstdint>
#include <string>

/**
 * The FourCC structure is used to represent magic words to identify data
 * formats
 */
#pragma pack(push, 1)
struct FourCC {
  union {
    uint32_t value = 0;
    char fourcc[4];
  };

  std::string ToString() { return std::string(fourcc, sizeof(fourcc)); }
};
#pragma pack(pop)

static_assert(sizeof(FourCC) == 4);
