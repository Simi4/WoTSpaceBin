#pragma once

#include <fstream>
#include <map>
#include <string>

#include "common/header_file.h"
#include "common/header_section.h"
#include "sections/section_bsma.h"
#include "sections/section_bsmi.h"
#include "sections/section_bsmo.h"
#include "sections/section_bwst.h"
#include "sections/section_bwt2.h"

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
 */
class SpaceBin
{
  public:
    explicit SpaceBin(std::istream &stream);
    ~SpaceBin();

    SectionBSMA GetBSMA();
    SectionBSMO GetBSMO();
    SectionBSMI GetBSMI();
    SectionBWST GetBWST();
    SectionBWT2 GetBWT2();

  private:
    void readHeaders();

    std::istream &_stream;

    FileHeader fileHeader{};

    std::map<std::string, SectionHeader> sectionHeaders;
};
