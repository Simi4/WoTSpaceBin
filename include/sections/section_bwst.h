#pragma once

#include <cstdint>
#include <fstream>
#include <map>
#include <vector>

#include "common/array.h"
#include "common/header_section.h"
#include "sections/section_base.h"

typedef uint32_t EntryID;

#pragma pack(push, 1)
struct BWSTEntry {
	EntryID id = 0;
	uint32_t offset = 0;
	uint32_t length = 0;
};
#pragma pack(pop)

static_assert(sizeof(BWSTEntry) == 12);

/**
 * BigWorld String Table
 *
 * A string table is provided in order to avoid having duplicated strings through-out the space binary, and also to
 * provide easy support for fixed-size structures that contain string references.
 *
 * The string table exists as it's own section in the binary format.
 *
 * Strings can be anything, from gameplay tokens to resource ID's.
 * Any non-ASCII strings should be encoded in UTF-8.
 */
class SectionBWST : public SectionBase {
public:
	explicit SectionBWST(std::ifstream& stream, SectionHeader& header);

	std::vector<uint8_t> GetString(EntryID id);

private:
	std::map<EntryID, std::vector<uint8_t>> _data;

	static constexpr uint32_t _supported_version = 2;
};