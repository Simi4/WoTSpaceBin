#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

#include "common/array.h"
#include "common/header_section.h"
#include "common/typedefs.h"
#include "sections/section_base.h"

class SectionBWT2 : public SectionBase
{
  public:
    explicit SectionBWT2(std::istream &stream, SectionHeader &header);

  private:
    static constexpr uint32_t _supported_version = 3;
};