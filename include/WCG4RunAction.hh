
#ifndef B5RunAction_h
#define B5RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"


class G4Run;

/// Run action class

class WCG4RunAction : public G4UserRunAction
{
  public:
    WCG4RunAction();
    virtual ~WCG4RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

};


#endif
