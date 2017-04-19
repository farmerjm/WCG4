#include "G4RunManager.hh"
#include "G4UImanager.hh"


#include "WCG4DetectorConstruction.hh"
#include "WCG4ActionInitialization.hh"
#include "WCG4SteppingAction.hh"
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

#include "Randomize.hh"

//Need to define a custom class that extends the G4Physics list and redefine its abstract methods
//Perhaps the best course of action here is to look at the source code from WCSim and steal things.
//example code taken from user manual


int main() { // construct the default run manager

  G4RunManager *runManager = new G4RunManager;

  //build world geometry (taken from p. 6-8)

  WCG4PhysListConfig* conf = new WCG4PhysListConfig();
  WCG4PhysListFactory* fact = new WCG4PhysListFactory(conf);
  G4VModularPhysicsList* physicsList = fact->BuildPhysicsList();



  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new WCG4DetectorConstruction);
  runManager->SetUserInitialization(new WCG4ActionInitialization);

  //Cherenkov counting / photon tracking
  runManager->SetUserAction(new WCG4SteppingAction);

  // initialize G4 kernel
  runManager->Initialize();
  // get the pointer to the UI manager and set verbosities
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 0");
  // start a run
  int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);
  // job termination
  delete runManager;
  return 0;
}
