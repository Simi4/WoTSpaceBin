#pragma once

#include <cstdint>
#include <fstream>

#include "common/header_section.h"
#include "sections/section_base.h"
#include "sections/section_bwst.h"

typedef uint32_t AssetType;

enum class AssetTypeEnum : uint32_t {
    ASSET_TYPE_UNKNOWN_TYPE = 0,
    ASSET_TYPE_DATASECTION  = 1,
    ASSET_TYPE_TEXTURE      = 2,
    ASSET_TYPE_EFFECT       = 3,
    ASSET_TYPE_PRIMITIVE    = 4,
    ASSET_TYPE_VISUAL       = 5,
    ASSET_TYPE_MODEL        = 6,
};

#pragma pack(push, 1)
struct BWALAssetListEntry
{
    AssetType type;

    /**
     * Points to BWST entry
     */
    EntryID resourceID;
};
#pragma pack(pop)

static_assert(sizeof(BWALAssetListEntry) == 8);

/**
 * BigWorld Asset List
 *
 * The asset list is a simple flat list of all assets used in the space (e.g. models, effects, ...).
 *
 * All assets of the same time are loaded together at the beginning of space loading.
 */
class SectionBWAL : public SectionBase {
public:
    explicit SectionBWAL(std::ifstream& stream, SectionHeader& header);

    Array<BWALAssetListEntry>& GetEntries();

private:
    static constexpr uint32_t _supported_version = 2;

    Array<BWALAssetListEntry> _entries;
};