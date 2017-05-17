#include "G4PhysListFactory.hh"
#include "globals.hh"
#include "WCG4PhysList.hh"
#include "G4OpticalPhysics.hh"

//The idea:
//PhysListFactory-> ModularPhysicsList
//Configurations can turn on or off specific processes, like delta rays or pair production. 
class WCG4PhysListFactory : public G4PhysListFactory
{

  std::string referenceListName;

public:

  WCG4PhysListFactory();
  ~WCG4PhysListFactory();


  WCG4PhysList* BuildPhysicsList();
};
