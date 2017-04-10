
#ifndef WCG4PhysicsList_h
#define WCG4PhysicsList_h 1
//#include "G4VUserPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "WCG4PhysicsMessenger.hh"
#include "globals.hh"

//class WCG4PhysicsList: public G4VUserPhysicsList
class WCG4PhysicsList: public G4VPhysicsConstructor
{
  public:
    WCG4PhysicsList();
    ~WCG4PhysicsList();

  //=================================
  // Added by JLR 2005-07-05
  //=================================
  // This method sets the model for 
  // hadronic secondary interactions
  void SetSecondaryHad(G4String hadval);
  G4String GetSecondaryHadModel() {return SecondaryHadModel;}
  
  private:
    WCG4PhysicsMessenger* PhysicsMessenger;

    G4String SecondaryHadModel;

    G4bool gheishahad;
    G4bool bertinihad;
    G4bool binaryhad;

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

  protected:
    // these methods Construct particles 
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();

  protected:
    // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();
    void ConstructOp();
    void ConstructHad();
    void ConstructlArStepLimiter();


};

#endif







