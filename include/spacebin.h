#pragma once

#include <fstream>
#include <map>
#include <string>

#include "common/header_file.h"
#include "common/header_section.h"

#include "sections/section_bsma.h"
#include "sections/section_bsmo.h"
#include "sections/section_bwal.h"
#include "sections/section_bwcs.h"
#include "sections/section_bwst.h"
#include "sections/section_bwwa.h"
#include "sections/section_wgsd.h"

/**
 * Compiled Space Binary
 *
 * The space.bin itself is a container format which allows a common way for
 * individual subsystems to store their own data.
 *
 * Section data are treated as raw blobs of data, and it is up to individual
 * subsystems to define and parse their own data blob.
 *
 * All values are written to disk in little endian format.
 *
 * Compiled spaces are designed to be as compact as possible on disk, with as
 * much data pre-processed as possible. As such, binary data tends to be raw
 * arrays of C++ structures, serialized directly to disk. This allows fast
 * loading by simply mapping parts of the binary file into memory as necessary
 * and setting pointers to the beginning of the data.
 *
 * OK:
 *   * BSMA::V1
 *   * BWAL::V2
 *   * BWCS::V1
 *   * BWST::V2
 *
 *  BROKEN
 *   * BWWa::V2 (actual size is 336, expected is 28)
 *   * WGSD::V2 (actual size is 2, expected is 112)
 *
 * MISSING:
 *   * BWSG::V2
 *   * BSGD::V2
 *   * BWS2::V2
 *   * BSG2::V2
 *   * CENT::V1
 *   * SpTr::V3
 *   * BWEP::V4
 *   * UDOS::V1
 *   * WGCO::V1
 *   * WGDE::V1
 *   * WGMM::V1
 *   * WGSH::V1
 *   * WTbl::V0
 *
 * OUTDATED SPEC, BUT IMPLEMENTED:
 *   * BSMO::V1 --> BSMO::V2
 *
 * OUTDATED SPEC:
 *   * BWLC::V1 --> BWLC::V2
 *   * BWPs::V1 --> BWPs::V2
 *   * BWT2::V1 --> BWT2::V3
 *   * BSMI::V1 --> BSMI::V3
 *
 *   * WTAu::V2 --> WTAu::V3
 *   * WTCP::V1 --> WTCP::V2
 *
 * NOT NEEDED:
 *   * BWfr::V1
 *   * BWSN::V1
 *   * BWSS::V1
 *   * WSMI::V1
 *   * WSMO::V1
 *
 */
class SpaceBin {
 public:
  explicit SpaceBin(std::ifstream& stream);
  ~SpaceBin();

  SectionBSMA GetBSMA();
  SectionBSMO GetBSMO();
  SectionBWAL GetBWAL();
  SectionBWCS GetBWCS();
  SectionBWST GetBWST();
  SectionBWWa GetBWWa();
  SectionWGSD GetWGSD();

 private:
  void readHeaders();

  std::ifstream& _stream;

  FileHeader fileHeader{};

  std::map<std::string, SectionHeader> sectionHeaders;
};
