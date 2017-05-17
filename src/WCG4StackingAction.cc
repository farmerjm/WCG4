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
    if (!gConfig->doDeltaRays && aTrack->GetCreatorProcess()->GetProcessName()=="muIoni") return fKill;
  }
  //muPairProd, muBrems, msc
  return fUrgent;
}

void WCG4StackingAction::NewStage() {
 G4cout << "Number of optphot in this event: " << optCounter << G4endl;
}

void WCG4StackingAction::PrepareNewEvent() {
  optCounter=0;
  photonCounter=0;
}
