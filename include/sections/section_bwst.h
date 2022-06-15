#pragma once

#include <cstdint>
#include <fstream>
#include <map>
#include <vector>

#include "common/array.h"
#include "common/header_section.h"
#include "common/typedefs.h"
#include "sections/section_base.h"

#pragma pack(push, 1)
struct BWSTEntry
{
    EntryID id = 0;
    uint32_t offset = 0;
    uint32_t length = 0;
};
#pragma pack(pop)

static_assert(sizeof(BWSTEntry) == 12);

class SectionBWST : public SectionBase
{
  public:
    explicit SectionBWST(std::ifstream &stream, SectionHeader &header);

    std::string_view GetString(uint32_t id);

  private:
    std::map<uint32_t, std::string> _data;

    static constexpr uint32_t _supported_version = 2;
};