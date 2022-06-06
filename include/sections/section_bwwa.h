#pragma once

#include <cstdint>
#include <fstream>

#include "common/array.h"
#include "common/header_section.h"
#include "sections/section_base.h"
#include "sections/section_bwst.h"

#pragma pack(push, 1)

struct BWWaWaterEntry {
  uint32_t state = 0;  // BW::Water::WaterState
  EntryID foamTexture = 0;
  EntryID waveTexture = 0;
  EntryID reflectionTexture = 0;
  EntryID transparencyTable = 0;
  uint32_t subBoundsBegin = 0;
  uint32_t subBoundsEnd = 0;
};

#pragma pack(pop)

static_assert(sizeof(BWWaWaterEntry) == 28);

/**
 * BigWorld Water
 *
 */
class SectionBWWa : public SectionBase {
 public:
  explicit SectionBWWa(std::ifstream& stream, SectionHeader& header);

  Array<BWWaWaterEntry>& GetWaterEntries();

 private:
  static constexpr uint32_t _supported_version = 2;

  Array<BWWaWaterEntry> _waterEntries;
};
