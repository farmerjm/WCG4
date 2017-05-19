#include "WCG4SimManager.hh"

WCG4SimManager::WCG4SimManager() {
  runID=0;
  start = 150;
  end = 3000; 
  numEvents=250;
  UI = G4UImanager::GetUIpointer();
}

void WCG4SimManager::ConfigureRunPhysics(WCG4SimConfig* theConf) {
  gConfig = theConf; 
  if (gConfig->doMuonIonization) UI->ApplyCommand("process/activate muIoni"); else UI->ApplyCommand("process/deactivate muIoni");
  if (gConfig->doPairProd) {
    UI->ApplyCommand("process/activate msc");
    UI->ApplyCommand("process/activate muBrems");
    UI->ApplyCommand("process/activate muPairProd");
  } else {
    UI->ApplyCommand("process/deactivate msc");
    UI->ApplyCommand("process/deactivate muBrems");
    UI->ApplyCommand("process/deactivate muPairProd");
  }
}


void WCG4SimManager::GenerateStandardConfigs() {
  WCG4SimConfig* muIon = new WCG4SimConfig(0,1,0,"MuIon");
  WCG4SimConfig* pp = new WCG4SimConfig(1,1,0, "PP");
  WCG4SimConfig* dr = new WCG4SimConfig(0,1,1, "DeltaRay");
  WCG4SimConfig* all = new WCG4SimConfig(1,1,1, "All");

  AddConfig(muIon);
  AddConfig(pp);
  AddConfig(dr);
  AddConfig(all);
}

void WCG4SimManager::EndRun() {
  
}

void WCG4SimManager::CalculateVEM() {
  const WCG4StackingAction* stack = dynamic_cast<const WCG4StackingAction*>(G4RunManager::GetRunManager()->GetUserStackingAction());
  runID=0;
  for (auto conf: configList) {
    ConfigureRunPhysics(conf);
    UI->ApplyCommand("/gun/energy 1.08 GeV");
    G4String sNumEvents = std::to_string(numEvents);
    G4String beamcmd = "/run/beamOn " + sNumEvents;
    UI->ApplyCommand(beamcmd);
    /*const std::vector<unsigned int> & data = stack->photDat;
    double mean = std::accumulate(data.begin(), data.end(), 0.0)/data.size();
    std::vector<double> diff(data.size());
    std::transform(data.begin(), data.end(), diff.begin(), [mean](double x) {return x - mean;});
    double std= std::sqrt(std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0)/data.size());
    VEMList.push_back(mean);
    VEMSigmaList.push_back(std);
    G4cout << "VEM calculated:  " << mean << " +/- " << std << G4endl;*/
    runID++;
  }
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

void WCG4SimManager::RunSimAllConfigs(double granularity) {

  UI = G4UImanager::GetUIpointer();
  G4RunManager* runManager = G4RunManager::GetRunManager();
  const WCG4StackingAction* stack = dynamic_cast<const WCG4StackingAction*>(runManager->GetUserStackingAction());

  std::vector<double> eVec;
  for (double d=start; d < end; d+=granularity) eVec.push_back(d);

  for (auto conf : configList) {
    std::vector<double> MuonCurve;
    std::vector<double> MuonCurveSigma;
    ConfigureRunPhysics(conf); 
    for (auto d : eVec) {
      std::vector<double> data;
      G4String energy=std::to_string(d);
      G4String eCmd = "/gun/energy " + energy + " MeV";
      UI->ApplyCommand(eCmd);
      for (int i=0; i< numEvents; i++) {
        UI->ApplyCommand("/run/beamOn 1");
        data.push_back(photonCounter);
      }
      double mean = std::accumulate(data.begin(), data.end(), 0.0)/data.size();
      std::vector<double> diff(data.size());
      std::transform(data.begin(), data.end(), diff.begin(), [mean](double x) {return x - mean;});
      double std= std::sqrt(std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0)/data.size());
      MuonCurve.push_back(mean);
      MuonCurveSigma.push_back(std);
    }
    MuonCurves.push_back(MuonCurve);
    MuonCurvesSigma.push_back(MuonCurveSigma);
    EndRun();
  }
}

WCG4SimManager* WCG4SimManager::instance;

WCG4SimManager* WCG4SimManager::Instance() {
  if (WCG4SimManager::instance == 0) WCG4SimManager::instance=CreateInstance();
  return WCG4SimManager::instance;

}
