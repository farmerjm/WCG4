#include "WCG4RunAction.hh"
#include "WCG4Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCG4RunAction::WCG4RunAction()
 : G4UserRunAction()
{ 
  G4cout << "Run manager" << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();

  // Default settings

  // Creating 1D histograms
  auto simManager = WCG4SimManager::Instance();
  G4cout << "nConfig: " << simManager->GetConfigs().size() << G4endl;
  for (auto conf : simManager->GetConfigs()) {
    G4String str = G4String("VEM: ") + G4String(conf->title);
    G4int intid = analysisManager->CreateH1(str,str, 20, 30000, 55000);
    G4cout << "Made histo " << intid << G4endl;
  }
  analysisManager->OpenFile("out/VEM");
  G4cout << "Run manager end" << G4endl;
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
  /*auto WCG4SimManager = WCG4SimManager::Instance();
  G4String str = G4String("VEM: ") + G4String(gConfig->title);
  G4String fname = G4String("out/VEM") + G4String(gConfig->title);
  G4int intid = analysisManager->CreateH1(str,str, 25, 25000, 55000);
  G4cout << "Made histo " << intid << G4endl;
  analysisManager->OpenFile(fname);*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCG4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  //auto analysisManager = G4AnalysisManager::Instance();
  //analysisManager->Write();
  //analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
