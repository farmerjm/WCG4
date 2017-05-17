#include "WCG4SimManager.hh"

WCG4SimManager::WCG4SimManager() {
  runID=0;
  start = 150;
  end = 3000; 
  UI = G4UImanager::GetUIpointer();
}

void WCG4SimManager::ConfigureRunPhysics(WCG4SimConfig* theConf) {
  gConfig = theConf; 
  if (gConfig->doMuonIonization) UI->ApplyCommand("process/activate muIoni"); else UI->ApplyCommand("process/deactivate muIoni");
}


void WCG4SimManager::GenerateStandardConfigs() {
  WCG4SimConfig* bare = new WCG4SimConfig(0,0,0, "Bare");
  WCG4SimConfig* muIon = new WCG4SimConfig(0,1,0,"MuIon");
  WCG4SimConfig* pp = new WCG4SimConfig(1,1,0, "PP");
  WCG4SimConfig* dr = new WCG4SimConfig(0,1,1, "DeltaRay");
  WCG4SimConfig* all = new WCG4SimConfig(1,1,1, "All");

  AddConfig(bare);
  AddConfig(muIon);
  AddConfig(pp);
  AddConfig(dr);
  AddConfig(all);
}

void WCG4SimManager::EndRun() {
  
}

void WCG4SimManager::CalculateVEM() {
  const WCG4StackingAction* stack = dynamic_cast<const WCG4StackingAction*>(G4RunManager::GetRunManager()->GetUserStackingAction());
  for (auto conf: configList) {
    UI->ApplyCommand("/gun/energy 1.08 GeV");
    UI->ApplyCommand("/run/beamOn 1");
    VEMList.push_back(static_cast<double>(stack->GetNumPhotons()));
    G4cout << "VEM calculated:  " << stack->GetNumPhotons() << G4endl;
  }
}

void WCG4SimManager::RunSimAllConfigs(double granularity) {

  G4RunManager* runManager = G4RunManager::GetRunManager();
  const WCG4StackingAction* stack = dynamic_cast<const WCG4StackingAction*>(runManager->GetUserStackingAction());

  std::vector<double> eVec;
  for (double d=start; d < end; d+=granularity) eVec.push_back(d);

  for (auto conf : configList) {
    std::vector<double> dat;
    ConfigureRunPhysics(conf); 
    for (auto d : eVec) {
      G4String energy=std::to_string(d);
      G4String eCmd = "/gun/energy " + energy + " MeV";
      UI->ApplyCommand(eCmd);
      UI->ApplyCommand("/run/beamOn 1");
      dat.push_back(static_cast<double>(stack->GetNumPhotons()));
    }
    dataList.push_back(dat);
    EndRun();
  }
  G4cout << "Done." << G4endl;
}
