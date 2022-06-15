#pragma once

#include <cstdint>
#include <fstream>

#include "common/array.h"
#include "common/header_section.h"
#include "common/matrix.h"
#include "common/typedefs.h"
#include "sections/section_base.h"

#pragma pack(push, 1)

struct BSMIChunkModel
{
    uint32_t casts_shadow : 1;
    uint32_t pad1 : 1;
    uint32_t casts_local_shadow : 1;
    uint32_t not_ignores_objects_farplane : 1;
    uint32_t always_dynamic : 1;
    uint32_t has_animations : 1;
    uint32_t unknown1 : 1;
    uint32_t pad2 : 25;
    uint32_t unknown;
};
static_assert(sizeof(BSMIChunkModel) == 8);

struct BSMIModelId
{
    ListIndex bsmo_model_id;
    ListIndex unknown;
};
static_assert(sizeof(BSMIModelId) == 8);

#pragma pack(pop)

class SectionBSMI : public SectionBase
{
  public:
    explicit SectionBSMI(std::istream &stream, SectionHeader &header);

    std::span<Matrix> GetTransforms();
    std::span<BSMIChunkModel> GetChunkModels();
    std::span<uint32_t> GetVisibilityMasks();
    std::span<BSMIModelId> GetModelIds();

  private:
    static constexpr uint32_t _supported_version = 3;

    std::vector<Matrix> _transforms;
    std::vector<BSMIChunkModel> _chunkModels;
    std::vector<uint32_t> _visibilityMasks;
    std::vector<BSMIModelId> _modelIds;
};
