#include "WCG4PhysListFactory.hh"


WCG4PhysListFactory::WCG4PhysListFactory(WCG4PhysListConfig* theConfig) {
  referenceListName="QGSP_BIC_HP";
}


WCG4PhysListFactory::~WCG4PhysListFactory() {

}

WCG4PhysList* WCG4PhysListFactory::BuildPhysicsList() {

  G4VModularPhysicsList* list = GetReferencePhysList(referenceListName);
  WCG4PhysList* outlist = new WCG4PhysList();
  for (G4int i = 0; ; ++i) {
    G4VPhysicsConstructor* elem =
      const_cast<G4VPhysicsConstructor*> (list->GetPhysics(i));
    if (elem == NULL) break;
    G4cout << "RegisterPhysics: " << elem->GetPhysicsName() << G4endl;
    outlist->RegisterPhysics(elem);
  }
  G4cout << "RegisterPhysics: OpticalPhysics" << G4endl; 
  G4OpticalPhysics* ophys = new G4OpticalPhysics();
  outlist->RegisterPhysics(ophys);

  //Here, search the config and selectively disable processes
  return outlist;
}


