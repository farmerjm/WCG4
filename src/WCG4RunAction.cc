#include "WCG4RunAction.hh"
#include "WCG4Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCG4RunAction::WCG4RunAction()
 : G4UserRunAction()
{ 
  auto analysisManager = G4AnalysisManager::Instance();

  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("WCG4out");

  // Creating 1D histograms
  WCG4SimManager* simMan = WCG4SimManager::Instance();
  for (auto conf : simMan->GetConfigs()) {
    G4String str = G4String("VEM: ") + G4String(conf->title);
    G4int intid = analysisManager->CreateH1(str,str, 20, 30000, 50000);
    G4cout << "Made histo:  id=" << intid << G4endl;
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCG4RunAction::~WCG4RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCG4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCG4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
