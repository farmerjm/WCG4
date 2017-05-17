#include "WCG4SimManager.hh"

WCG4SimManager::WCG4SimManager() {
  runID=0;
}

WCG4SimManager::ConfigureRunPhysics() {
  gConfig = configList.at(runID); 
}


WCG4SimManager::RunSim(double granularity) {

  G4UImanager *UI = G4UImanager::GetUIpointer();

  for (int i=0; i<configList.size(); i++) {
    ConfigureRunPhysics(i); 
    UI->ApplyCommand("/gun/energy 2 GeV");
    UI->ApplyCommand("/run/beamOn 1");
  }

}
