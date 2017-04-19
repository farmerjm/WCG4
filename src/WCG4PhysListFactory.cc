#include "WCG4PhysListFactory.hh"


WCG4PhysListFactory::WCG4PhysListFactory(WCG4PhysListConfig* theConfig) {
  referenceListName="FTFP_BERT_EMV";
}


WCG4PhysListFactory::~WCG4PhysListFactory() {



}

G4VModularPhysicsList* WCG4PhysListFactory::BuildPhysicsList() {

  G4VModularPhysicsList* list = GetReferencePhysList(referenceListName);

  //Here, search the config and selectively disable processes
  return list;
}

