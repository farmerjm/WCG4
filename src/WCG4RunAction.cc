#include "WCG4RunAction.hh"
#include "WCG4Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCG4RunAction::WCG4RunAction()
 : G4UserRunAction()
{ 
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B5Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("WCG4out");

  // Creating 1D histograms
  analysisManager
    ->CreateH1("","Drift Chamber 1 # Hits", 50, 0., 50); // h1 Id = 0
  analysisManager
    ->CreateH1("Chamber2","Drift Chamber 2 # Hits", 50, 0., 50); // h1 Id = 1
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B5RunAction::~B5RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B5RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
