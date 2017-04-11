#include "G4RunManager.hh"
#include "G4UImanager.hh"



#include "WCG4DetectorConstruction.hh"
#include "WCG4ActionInitialization.hh"

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

  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);


  runManager->SetUserInitialization(new WCG4DetectorConstruction);
  runManager->SetUserInitialization(new WCG4ActionInitialization);

  //runManager->SetUserInitialization(new ExG4PhysicsList00);

  // initialize G4 kernel
  runManager->Initialize();
  // get the pointer to the UI manager and set verbosities
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");
  // start a run
  int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);
  // job termination
  delete runManager;
  return 0;
}
