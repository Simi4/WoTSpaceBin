#pragma once

#include <cstdint>
#include <fstream>

#include "common/bbox.h"
#include "common/header_section.h"
#include "sections/section_base.h"

/**
 * BigWorld Space Settings
 *
 * The space settings is small amount of meta data which describes the space as a whole
 */
class SectionBWCS : public SectionBase {
public:
    explicit SectionBWCS(std::ifstream& stream, SectionHeader& header);

    Bbox GetSpaceBounds();

private:
    static constexpr uint32_t _supported_version = 1;

    /**
     * The spaceBounds should contain the entire bounds of all objects in the space
     * (including "out-land" items that may not originally fall inside the terrain region).
     */
    Bbox _spaceBounds;
};
