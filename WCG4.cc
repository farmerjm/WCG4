#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "WCG4DetectorConstruction.hh"
#include "WCG4ActionInitialization.hh"
#include "WCG4PhysListConfig.hh"
#include "WCG4PhysListFactory.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "common.hh"
#include "Randomize.hh"

int numCherenkov;
int photonCounter;

int main() { // construct the default run manager

  G4RunManager *runManager = new G4RunManager;

  WCG4PhysListConfig* conf = new WCG4PhysListConfig();
  WCG4PhysListFactory* fact = new WCG4PhysListFactory(conf);
  WCG4PhysList* physicsList = fact->BuildPhysicsList();

  for (G4int i = 0; ; ++i) {
    G4VPhysicsConstructor* elem = const_cast<G4VPhysicsConstructor*> (physicsList->GetPhysics(i));
    if (elem == NULL) break;
    G4cout << "FINAL LIST: " << elem->GetPhysicsName() << G4endl;
  }

  numCherenkov=0;
  photonCounter=0;

  runManager->SetUserInitialization(new WCG4DetectorConstruction);
  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new WCG4ActionInitialization);

  //initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the UI manager and set verbosities
  G4VisExecutive* visManager = new G4VisExecutive();
  visManager->Initialize();
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");
  UI->ApplyCommand("/control/execute vis.mac");

  int numberOfEvent = 1;
  runManager->BeamOn(numberOfEvent);
  // job termination
  G4cout << numCherenkov << " " << photonCounter << G4endl;
  delete runManager;
  return 0;
}
