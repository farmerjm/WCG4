#include "WCG4DetectorConstruction.hh"
#include "globals.hh"
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
  fScoringVolume(0),
  waterMPT(new G4MaterialPropertiesTable()),
  tyvekMPT(new G4MaterialPropertiesTable()),
  linerMPT(new G4MaterialPropertiesTable()),
  HDPE(nullptr);
{
  ConstructMaterials(); 
}

WCG4DetectorConstruction::~WCG4DetectorConstruction()
{
  
}

void WCG4DetectorConstruction::ConstructMaterials() {
  DefineMaterialConstants();
  ConstructWater();
  ConstructHDPE();
  ConstructLinerOpSurface();
}

void WCG4DetectorConstruction::DefineMaterialConstants() {

  double def_eBins[30] = {  
    2.08, 2.16, 2.19, 2.23, 2.27, 2.32,
    2.36, 2.41, 2.46, 2.50, 2.56, 2.61,
    2.67, 2.72, 2.79, 2.85, 2.92, 2.99,
    3.06, 3.14, 3.22, 3.31, 3.40, 3.49,
    3.59, 3.70, 3.81, 3.94, 4.07, 4.20};

  for (int i=0;i <30;i++) eBins[i]=def_eBins[i]*eV;

  double def_tyvekReflectivity[30] = {
    0.9957, 0.9953, 0.9948, 0.9942, 0.9939, 0.9937,
    0.9937, 0.9940, 0.9945, 0.9954, 0.9964, 0.9975,
    0.9985, 0.9993, 1.0000, 1.0000, 0.9993, 0.9977,
    0.9948, 0.9903, 0.9840, 0.9753, 0.9642, 0.9500,
    0.9334, 0.9108, 0.8849, 0.8541, 0.8178, 0.7755};

  for (int i=0;i <30;i++) tyvekReflectivity[i]=def_tyvekReflectivity[i]*0.94;

  double def_absLength[30] = {
    0.092, 0.133, 0.180, 0.203, 0.226, 0.258,
    0.284, 0.302, 0.403, 0.560, 0.735, 0.818,
    0.923, 0.923, 0.993, 0.993, 1.000, 0.941,
    0.889, 0.842, 0.754, 0.655, 0.480, 0.380,
    0.311, 0.257, 0.212, 0.171, 0.137, 0.102};

  for (int i=0;i <30;i++) absLength[i]=def_absLength[i]*m;

  double def_zeroes[30] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0};

  for (int i=0; i<30; i++) zeroes[i]=def_zeroes[i];

}
void WCG4DetectorConstruction::ConstructWater() {

  double waterRindex[2] = {1.33, 1.33};
  double waterRindexEbins[2] = {2.08, 4.20};

  waterMPT->AddProperty("RINDEX", waterRindexEbins, waterRindex,2);
  waterMPT->AddProperty("ABSLENGTH", eBins, absLength,30);

}

void ConstructHDPE() {
  G4double denisty= 0.943*g/cm3;
  G4int nel, natoms;
  G4String name;

  HDPE = new G4Material(name="HDPE", density, ne1=2);
  HDPE->AddElement(elC, natoms=2);
  HDPE->AddElement(elH, natoms=4);

  linerMPT->AddProperty("ABSLENGTH", waterRindexEBins, tyvekReflectivity,30); 

  HDPE->SetMaterialPropertiesTable(linerMPT);

  return;
}

void ConstructLinerOpSurface {
  double SigmaAlpha=0.17;
  double specBins[3] = {2.08*eV, 3.0*eV, 4.20*eV};
  double specLobe[3] = {0.2, 0.2, 0.2};
  double specSpike[3] = {0, 0, 0};

  linerMPT->AddProperty("BACKSCATTERCONSTANT", eBins, zeroes, 30);
  linerMPT->AddProperty("RINDEX", eBins, zeroes, 30);
  linerMPT->AddProperty("REFLECTIVITY", eBins, tyvekReflectivity, 30);
  linerMPT->AddProperty("SPECULARSPIKECONSTANT", specBins, specSpike, 3);
  linerMPT->AddProperty("SPECULARLOBECONSTANT", specBins, specLobe, 3);

  LinerOpSurface = new G4OpticalSurface("WallSurface");

  LinerOpSurface->SetModel(unified);
  LinerOpSurface->SetType(dielectric_dielectric);
  LinerOpSurface->SEtFinish(groundbackpainted);
  LinerOpSurface->SetSigmaAlpha(SigmaAlpha);
  LinerOpSurface->SetMaterialPropertiesTable(linerMPT);
}

//Is scoring volume set to the correct thing?
G4VPhysicalVolume* WCG4DetectorConstruction::Construct()
{

  //dimensions:
  G4double worlddim=1.0*m;
  G4double tankRadius=1.8*m;
  G4double tankHeight=1.2*m;
  G4double wallThickness=1.22*cm;

  //Now, define materials from internal G4 databases:
  G4NistManager* man = G4NistManager::Instance();
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
  G4Material* Water = man->FindOrBuildMaterial("G4_WATER");
  Water->SetMaterialPropertiesTable(waterMPT);
  //G4Material* Polyethylene = man->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Vacuum = new G4Material("Vacuum",1., 1.101*g/mole, 1.e-9*g/cm3, kStateGas,0.1*kelvin, 1.e-19*pascal);

  //create shapes:
  G4Box* worldBox = new G4Box("World", 2*worlddim, 2*worlddim, worlddim);
  G4Tubs* Tank = new G4Tubs("Tank", 0,  tankRadius, tankHeight/2, 0.*deg, 360.*deg); 
  G4Tubs* Sidewalls = new G4Tubs("Sidewalls",tankRadius, tankRadius+wallThickness, tankHeight/2, 0.*deg, 360.*deg);
  G4Tubs* Topwalls = new G4Tubs("Topwalls",0, tankRadius+wallThickness, wallThickness/2, 0.*deg, 360.*deg);
  G4Tubs* Bottomwalls = new G4Tubs("Bottomwalls",0, tankRadius+wallThickness, wallThickness/2, 0.*deg, 360.*deg);

  //Next, create logical volumes by matching the shapes with materials
  G4LogicalVolume* logWorld = new G4LogicalVolume(worldBox,Vacuum, "World");
  G4LogicalVolume* logTank = new G4LogicalVolume(Tank, Water, "Tank"); 
  G4LogicalVolume* logSidewalls = new G4LogicalVolume(Sidewalls, HDPE, "Sidewalls");  
  G4LogicalVolume* logTopwalls = new G4LogicalVolume(Topwalls, HDPE, "Topwalls");  
  G4LogicalVolume* logBottomwalls = new G4LogicalVolume(Bottomwalls, HDPE, "Bottomwalls");  

  G4ThreeVector centroid = G4ThreeVector(0,0,0);
  G4ThreeVector vTopwalls = G4ThreeVector(0,0,(tankHeight+wallThickness)/2);
  G4ThreeVector vBottomwalls = G4ThreeVector(0,0,-(tankHeight+wallThickness)/2);

  G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr,centroid, logWorld,"World", nullptr, false, 0);
  G4VPhysicalVolume* physTank = new G4PVPlacement(nullptr, centroid, logTank, "Tank", logWorld, false, 1);
  G4VPhysicalVolume* physSidewalls = new G4PVPlacement(nullptr,centroid, logSidewalls, "Sidewalls", logWorld, false, 2);
  G4VPhysicalVolume* physTopwalls = new G4PVPlacement(nullptr,vTopwalls, logTopwalls, "Topwalls", logWorld, false, 2);
  G4VPhysicalVolume* physBottomwalls = new G4PVPlacement(nullptr,vBottomwalls, logBottomwalls, "Bottomwalls", logWorld, false, 2);

  G4LogicalBorderSurface topSurface = new G4LogicalBorderSurface("topsurface", physTank, physTopwalls, LinerOpSurface);
  G4LogicalBorderSurface bottomSurface = new G4LogicalBorderSurface("bottomsurface", physTank, physBottomwalls, LinerOpSurface);
  G4LogicalBorderSurface wallSurface = new G4LogicalBorderSurface("wallsurface", physTank, physSideWalls, LinerOpSurface);

  

  //fScoringVolume = logTank;
  //What is this?
 
  return physWorld;
}

