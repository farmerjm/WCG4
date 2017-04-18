#include <stdlib.h>
#include <stdio.h>
#include "globals.hh"

#include "WCG4SteppingAction.hh"
//#include "G4SteppingVerbose.hh"
//#include "G4SteppingManager.hh"
//#include "G4VPhysicalVolume.hh"


void WCG4SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();

  const G4Track* track       = aStep->GetTrack();
  G4VPhysicalVolume* volume  = track->GetVolume();

  G4StepPoint* PostStep=aStep->GetPostStepPoint();

  //Is it a photon? If not, ignore it:  we do not need it.
  if (track->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition() ) return;

  //First, check that we are inside the region of interest:
  if (volume->GetName()=="Tank")
  {

    if (PostStep->GetProcessDefinedStep()->GetProcessName()=="Cerenkov")
    {
      //count Cherenkov photons:  check with calculation directly from Jackson
    }


    if (PostStep->GetStepStatus()==fGeomBoundary)
    {
      //If photon, then increment some counter
      //Check wavelength here
    }

  }
}

