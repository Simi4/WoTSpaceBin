#include <cassert>

#include "sections/section_bwcs.h"

SectionBWCS::SectionBWCS(std::ifstream& stream, SectionHeader& header) {
  assert(header.version == _supported_version);

  // move to section start
  stream.seekg(header.offset, stream.beg);

  stream.read(reinterpret_cast<char*>(&_spaceBounds), sizeof(_spaceBounds));
}

Bbox SectionBWCS::GetSpaceBounds() {
  return _spaceBounds;
}
