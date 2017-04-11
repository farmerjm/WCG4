#include <stdlib.h>
#include <stdio.h>

#include "WCG4SteppingAction.hh"

#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4VParticleChange.hh"
#include "G4SteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"


void WCG4SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();

  const G4Track* track       = aStep->GetTrack();
  G4VPhysicalVolume* volume  = track->GetVolume();

  G4StepPoint* PostStep=aStep->GetPostStepPoint();

  //Is it a photon? If not, ignore it:  we do not need it.
  G4Track* theTrack = GetTrack();
  if (theTrack->GetDefinition() != G4OpticalPhoton->OpticalPhotonDefinition() ) return;

  //First, check that we are inside the region of interest:

  G4PhysicalVolume* Mother = PostStep->GetTouchableHandle()->GetVolume();

  G4String MotherName=Mother->GetName();

  if (MotherName=="Tank")
  {

    if (PostStep->GetProcessDefinedStep()->GetProcessName()=="Cerenkov")
    {
      //count Cherenkov photons:  check with calculation directly from Jackson
    }


    if (PostStep->GetStepStatus==fGeomBoundary)
    {
      //If photon, then increment some counter
      //Check wavelength here
    }

  }

  
}

void WCG4SteppingAction::Distortion(G4double /*x*/,G4double /*y*/)
{
 
}


double WCG4SteppingAction::FieldLines(G4double /*x*/,G4double /*y*/,G4int /*coord*/)
{ 

  return 0;
}
