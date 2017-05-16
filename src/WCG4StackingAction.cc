#include "WCG4StackingAction.hh"


WCG4StackingAction::WCG4StackingAction() : optCounter(0) {

}

WCG4StackingAction::~WCG4StackingAction() {

}


G4ClassificationOfNewTrack WCG4StackingAction::ClassifyNewTrack(const G4Track* aTrack) {
  if (aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()) {
    optCounter++;

  }
  return fUrgent;
}

void WCG4StackingAction::NewStage() {
 G4cout << "Number of optphot in this event: " << optCounter << G4endl;
}

void WCG4StackingAction::PrepareNewEvent() {
  optCounter=0;
}
