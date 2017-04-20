#ifndef WCG4SteppingAction_h
#define WCG4SteppingAction_h 1
#include "G4Event.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4UserSteppingAction.hh"
#include "G4VPhysicalVolume.hh"
#include "common.hh"

class WCG4SteppingAction : public G4UserSteppingAction {

public:
  WCG4SteppingAction(){};
  ~WCG4SteppingAction(){};

  void UserSteppingAction(const G4Step *);
};

#endif
