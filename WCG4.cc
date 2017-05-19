#define G4_VIS_USE_OPENGLX

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "WCG4DetectorConstruction.hh"
#include "WCG4ActionInitialization.hh"
#include "WCG4PhysListFactory.hh"
#include "WCG4SimManager.hh"
#include "WCG4SimConfig.hh"

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
int numConfigs;
WCG4SimConfig* gConfig;


int main(int argc, char* argv[]) { // construct the default run manager

#ifdef G4MULTITHREADEDq
  G4cout << "Running in MT mode..." << G4endl;
  G4MTRunManager *runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(10);
#else
  G4RunManager *runManager = new G4RunManager;
#endif

  WCG4PhysListFactory* fact = new WCG4PhysListFactory();
  WCG4PhysList* physicsList = fact->BuildPhysicsList();

/*  for (G4int i = 0; ; ++i) {
    G4VPhysicsConstructor* elem = const_cast<G4VPhysicsConstructor*> (physicsList->GetPhysics(i));
    if (elem == NULL) break;
    G4cout << "FINAL LIST: " << elem->GetPhysicsName() << G4endl;
  } */

  numCherenkov=0;
  photonCounter=0;

  WCG4SimManager* man = WCG4SimManager::Instance();
  man->GenerateStandardConfigs();
  G4cout << "nConfigs: " << man->GetConfigs().size() << G4endl;
  runManager->SetUserInitialization(new WCG4DetectorConstruction);
  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new WCG4ActionInitialization);

  runManager->Initialize();

  //G4VisExecutive* visManager = new G4VisExecutive();
  //visManager->Initialize();
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");
  //UI->ApplyCommand("/control/execute vis.mac");
  //G4UIExecutive* session = new G4UIExecutive(argc, argv);
  //session->SessionStart();
  
  man->CalculateVEM();

  delete runManager;
  return 0;
}
