#include "WCG4StackingAction.hh"


WCG4StackingAction::WCG4StackingAction() : optCounter(0) {

}

WCG4StackingAction::~WCG4StackingAction() {

}


G4ClassificationOfNewTrack WCG4StackingAction::ClassifyNewTrack(const G4Track* aTrack) {
  if (aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()) {
    optCounter++;

  }
  if (aTrack->GetDefinition()==G4Electron::ElectronDefinition()) {
    if (aTrack->GetCreatorProcess()!=0) {
      if (!gConfig->doDeltaRays && aTrack->GetCreatorProcess()->GetProcessName()=="muIoni") return fKill;
    }
  }
  //muPairProd, muBrems, msc
  return fUrgent;
}

void WCG4StackingAction::NewStage() {
  photDat.push_back(photonCounter);
  auto analysisManager = G4AnalysisManager::Instance();
  auto simManager = WCG4SimManager::Instance();
  G4cout << "Filling..." << G4endl;
  analysisManager->FillH1(simManager->GetRunID(), photonCounter);
}

void WCG4StackingAction::PrepareNewEvent() {
  optCounter=0;
  photonCounter=0;
  photDat.clear();
}
