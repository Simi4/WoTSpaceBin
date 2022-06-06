#include <cassert>

#include "sections/section_bwwa.h"

SectionBWWa::SectionBWWa(std::ifstream& stream, SectionHeader& header) {
  assert(header.version == _supported_version);

  // move to section start
  stream.seekg(header.offset, stream.beg);

  _waterEntries = Array<BWWaWaterEntry>(stream);
}

Array<BWWaWaterEntry>& SectionBWWa::GetWaterEntries() {
  return _waterEntries;
}
