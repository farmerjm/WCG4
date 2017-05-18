#ifndef WCG4Stack
#define WCG4Stack

#include "G4UserStackingAction.hh"
#include "G4Track.hh"
#include "common.hh"
#include "G4VProcess.hh"
//#include "G4ParticleDefition.hh"
#include "G4ParticleTypes.hh"
#include "WCG4SimManager.hh"
#include "WCG4Analysis.hh"

class WCG4StackingAction :  public G4UserStackingAction {


public:
  WCG4StackingAction();
  virtual ~WCG4StackingAction();

  int GetNumPhotons() const {return optCounter;}
  
  std::vector<unsigned int> photDat;

private:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent(); 

  int optCounter;

};



#endif
