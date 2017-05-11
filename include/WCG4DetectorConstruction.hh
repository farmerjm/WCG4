//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1DetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "globals.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class WCG4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    WCG4DetectorConstruction();
    virtual ~WCG4DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    void ConstructMaterials();
    void DefineMaterialConstants();
    void DefineElements();
    void ConstructWater();
    void ConstructHDPE();
    void ConstructLinerOpSurface();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;

  private:

    G4double worlddim;
    G4double tankRadius;
    G4double tankHeight;
    G4double wallThickness;

    double eBins[30];
    double absLength[30];
    double linerAbsLength[30];
    double tyvekReflectivity[30];
    double zeroes[30];

    G4Element* elC;
    G4Element* elH;
    G4Element* elO;

    G4MaterialPropertiesTable* waterMPT;
    G4MaterialPropertiesTable* tyvekMPT;
    G4MaterialPropertiesTable* linerMPT;

    G4Material* HDPE;
    G4Material* elWater;
    G4Material* Vacuum;
  
    G4OpticalSurface* LinerOpSurface;

    //Volumes
    G4Box* worldBox;
    G4Tubs* Tank;
    G4Tubs* Sidewalls;
    G4Tubs* Bottomwalls;
    G4Tubs* Topwalls;

    G4LogicalVolume* logWorld;
    G4LogicalVolume* logTank;
    G4LogicalVolume* logSidewalls;
    G4LogicalVolume* logTopwalls;
    G4LogicalVolume* logBottomwalls;

    G4VPhysicalVolume* physWorld;
    G4VPhysicalVolume* physTank;
    G4VPhysicalVolume* physSidewalls;
    G4VPhysicalVolume* physTopwalls;
    G4VPhysicalVolume* physBottomwalls;

    G4LogicalBorderSurface* topSurface;
    G4LogicalBorderSurface* bottomSurface;
    G4LogicalBorderSurface* wallSurface;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

