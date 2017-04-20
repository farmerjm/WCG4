#include "WCG4SteppingAction.hh"

void WCG4SteppingAction::UserSteppingAction(const G4Step* aStep) {
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  const G4Track* track       = aStep->GetTrack();
  G4VPhysicalVolume* volume  = track->GetVolume();
  G4StepPoint* PostStep=aStep->GetPostStepPoint();

  //First, check that we are inside the region of interest:
  if (volume->GetName()=="Tank") {
    if (PostStep->GetProcessDefinedStep()->GetProcessName()=="Cerenkov") {  //count Cherenkov photons:  check with calculation directly from Jackson
      numCherenkov++;
      G4cout << "Cherenkov found " << G4endl;
    } if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && PostStep->GetStepStatus()==fGeomBoundary) {  //Check wavelength here
      photonCounter++;
      G4cout << "Photon exited" << G4endl;
    }
  }
}
