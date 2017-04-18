#include"G4PhysListFactory.hh"
#include"globals.hh"
#include"G4VModularPhysicsList.hh"
#include "WCG4PhysListConfig.hh"

class G4PhysListFactory;

//The idea:
//PhysListFactory-> ModularPhysicsList
//Configurations can turn on or off specific processes, like delta rays or pair production. 
class WCG4PhysListFactory : public G4PhysListFactory
{

  WCG4PhysListConfig* config;
  std::string referenceListName;

public:

  WCG4PhysListFactory(WCG4PhysListConfig* theConfig);
  ~WCG4PhysListFactory();


  G4VModularPhysicsList* BuildPhysicsList();
};
