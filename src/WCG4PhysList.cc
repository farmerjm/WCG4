#include "WCG4PhysList.hh"

void WCG4PhysList::SetCuts() {
  SetCutValue(defaultCut, "gamma");
  SetCutValue(defaultCut, "e-");
  SetCutValue(defaultCut, "e+");
  SetCutValue(defaultCut, "mu-");
  SetCutValue(defaultCut, "mu+");
}
