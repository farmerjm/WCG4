#include "globals.hh"
#include "G4VModularPhysicsList.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class WCG4PhysList : public G4VModularPhysicsList {
public:

  WCG4PhysList()
    {defaultCut=1.0*mm;} //Why won't mm compile?
  ~WCG4PhysList()
    {};


  void SetCuts();

private:
  
  double defaultCut;

};
