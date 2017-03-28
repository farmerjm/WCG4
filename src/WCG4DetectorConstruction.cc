#include "WCG4DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


WCG4DetectorConstruction::WCG4DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{
}

WCG4DetectorConstruction::~WCG4DetectorConstruction()
{
}


//Is scoring volume set to the correct thing?
G4VPhysicalVolume* WCG4DetectorConstruction::Construct()
{

  //dimensions:
  G4double worlddim=2.0*m;
  G4double tankRadius=1.8*m;
  G4double tankHeight=1.2*m;
  G4double wallThickness=1.22*cm;

  //create shapes:
  G4Box* worldBox = new G4Box("World", worlddim, worlddim, worlddim);
  G4Tubs* Tank = new G4Tubs("Tank", 0,  tankRadius, tankHeight, 0.*deg, 360.*deg); 
  G4Tubs* Walls = new G4Tubs("Walls",0, tankRadius, tankRadius+wallThickness, 0.*deg, 360.*deg);

  //Now, define materials from internal G4 databases:
  G4NistManager* man = G4NistManager::Instance();
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
  G4Material* Water = man->FindOrBuildMaterial("G4_WATER");
  G4Material* Polyethylene = man->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Vacuum = new G4Material("Vacuum",1., 1.101*g/mole, 1.e-5*g/cm3, kStateGas,0.1*kelvin, 1.e-19*pascal);

  //Next, create logical volumes by matching the shapes with materials
  G4LogicalVolume* logWorld = new G4LogicalVolume(worldBox,Vacuum, "World");
  G4LogicalVolume* logTank = new G4LogicalVolume(Tank, Water, "Tank"); 
  G4LogicalVolume* logWalls = new G4LogicalVolume(Walls, Polyethylene, "Walls");  

  G4ThreeVector centroid = G4ThreeVector(0,0,0);

  G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr,centroid, logWorld,"World", nullptr, false, 0);
  G4VPhysicalVolume* physTank = new G4PVPlacement(nullptr, centroid, logTank, "Tank", logWorld, false, 1);
  G4VPhysicalVolume* physWalls = new G4PVPlacement(nullptr,centroid, logWalls, "Walls", logWorld, false, 2);

  fScoringVolume = logTank;
  
  return physWorld;
}

