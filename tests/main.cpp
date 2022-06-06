#include <filesystem>
#include <iostream>
#include "spacebin.h"

int main() {
  namespace fs = std::filesystem;
  auto spacebin_path = fs::path("../tests/space.bin");
  if (!fs::exists(spacebin_path)) {
    std::cerr << spacebin_path << " doesn't exist!" << std::endl;
    return 1;
  }
  auto stream =
      std::ifstream(spacebin_path, std::ifstream::binary | std::ifstream::in);
  if (!stream) {
    std::cerr << spacebin_path << " couldn't open!" << std::endl;
    return 1;
  }
  SpaceBin s(stream);
  s.GetBWST();
  s.GetBWAL().GetEntries();
  s.GetBWCS().GetSpaceBounds();
  s.GetBSMA().GetEffects();
  // BROKEN: s.GetBWWa().GetWaterEntries();
  // BROEKN: s.GetWGSD().GetDecalEntries();
  s.GetBSMO().GetAnimations();
  return 0;
}
