#ifndef WCG4Stack
#define WCG4Stack

#include "G4UserStackingAction.hh"
#include "G4Track.hh"
//#include "G4ParticleDefition.hh"
#include "G4ParticleTypes.hh"

class WCG4StackingAction :  public G4UserStackingAction {


public:
  WCG4StackingAction();
  virtual ~WCG4StackingAction();

  int GetNumPhotons() const {return optCounter;}

private:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent(); 

  int optCounter;

};



#endif
