#include "spacebin.h"

int main() {
  auto stream = std::ifstream("D:\\Projects\\spacebin\\space.bin",
                              std::ifstream::binary | std::ifstream::in);
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