#pragma once

#include <cstdint>
#include <fstream>

#include "common/array.h"
#include "common/bbox.h"
#include "common/header_section.h"
#include "common/matrix.h"
#include "common/vector2.h"
#include "common/vector4.h"

#include "sections/section_base.h"
#include "sections/section_bwst.h"

#pragma pack(push, 1)

const uint32_t MAX_ATLAS_COUNT = 4;

struct WGSDDecal {
  uint8_t accuracyType;
  Matrix worldTransform;
  EntryID map[MAX_ATLAS_COUNT];
  uint8_t priority;
  uint8_t influenceType;
  uint8_t materialType;
  Vector4 offsets;
  Vector2 uvWrapping;
  uint32_t visibilityMask;
};
static_assert(sizeof(WGSDDecal) == 112);

struct WGSDDecalGroup {
  Bbox worldBB;
  uint32_t startIndex;
  uint32_t endIndex;
};
static_assert(sizeof(WGSDDecalGroup) == 32);

#pragma pack(pop)

/**
 * BigWorld Static Decal
 *
 */
class SectionWGSD : public SectionBase {
 public:
  explicit SectionWGSD(std::ifstream& stream, SectionHeader& header);

  Array<WGSDDecal>& GetDecalEntries();

 private:
  static constexpr uint32_t _supported_version = 2;

  Array<WGSDDecal> _decalEntries;
};
