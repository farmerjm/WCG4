#include "WCG4SteppingAction.hh"

void WCG4SteppingAction::UserSteppingAction(const G4Step* aStep) {
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  G4Track* track       = aStep->GetTrack();
  G4VPhysicalVolume* volume  = track->GetVolume();
  G4StepPoint* PreStep=aStep->GetPreStepPoint();
  G4StepPoint* PostStep=aStep->GetPostStepPoint();

  //First, check that we are inside the region of interest:
  if (volume->GetName()=="Tank") {
    if (PostStep->GetProcessDefinedStep()->GetProcessName()=="Cerenkov") {  //count Cherenkov photons:  check with calculation directly from Jackson
      numCherenkov++;
      //G4cout << "Cherenkov found " << G4endl;
    } if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && PostStep->GetStepStatus()==fGeomBoundary) {  //Check wavelength here
      photonCounter++;
      //G4cout << "Photon exited" << G4endl;
      track->SetTrackStatus(fStopAndKill);
    }
  }

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager) {
    G4Colour color;
    if (track->GetDefinition() == G4MuonMinus::MuonMinusDefinition()) color= G4Colour(0,0,1);
    if (track->GetDefinition() == G4Electron::ElectronDefinition()) color = G4Colour(1,0,0);
    if (track->GetDefinition() == G4Gamma::GammaDefinition()) color = G4Colour(1,0,1);
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) color = G4Colour(0,0,1);
    G4VisAttributes attribs(color);
    G4Polyline polyline;
    polyline.SetVisAttributes(attribs);
    polyline.push_back(PreStep->GetPosition());
    polyline.push_back(PostStep->GetPosition());
    pVVisManager->Draw(polyline);
  }


}
