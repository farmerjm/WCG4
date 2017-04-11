#ifndef WCG4SteppingAction_h
#define WCG4SteppingAction_h 1

#include "G4Event.hh"
#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"

class G4HCofThisEvent;
class G4Event;

class WCG4SteppingAction : public G4UserSteppingAction
{

public:
  WCG4SteppingAction()
  {};

  ~WCG4SteppingAction()
  {};

  void UserSteppingAction(const G4Step*);

  G4int G4ThreeVectorToWireTime(G4ThreeVector *pos3d,
				G4ThreeVector lArPos,
				G4ThreeVector start,
				G4int i);
  
  void Distortion(G4double x,
		  G4double y);

  G4double FieldLines(G4double x,
		      G4double y,
		      G4int xy);

private:

  G4double ret[2];

};


#endif
