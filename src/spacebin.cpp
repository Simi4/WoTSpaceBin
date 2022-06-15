#include "spacebin.h"

SpaceBin::SpaceBin(std::ifstream &stream) : _stream(stream)
{
    readHeaders();
}

SpaceBin::~SpaceBin()
{
    _stream.close();
}

void SpaceBin::readHeaders()
{
    _stream.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));

    for (auto sectionIdx = 0; sectionIdx < fileHeader.num_sections; sectionIdx++)
    {
        SectionHeader sectionHeader{};
        _stream.read(reinterpret_cast<char *>(&sectionHeader), sizeof(sectionHeader));
        sectionHeaders.emplace(sectionHeader.magic.ToString(), sectionHeader);
    }
}

SectionBSMA SpaceBin::GetBSMA()
{
    return SectionBSMA(_stream, sectionHeaders["BSMA"]);
}

SectionBSMO SpaceBin::GetBSMO()
{
    return SectionBSMO(_stream, sectionHeaders["BSMO"]);
}

SectionBWST SpaceBin::GetBWST()
{
    return SectionBWST(_stream, sectionHeaders["BWST"]);
}
