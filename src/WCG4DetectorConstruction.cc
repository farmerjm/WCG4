#include "WCG4DetectorConstruction.hh"


WCG4DetectorConstruction::WCG4DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
  waterMPT(new G4MaterialPropertiesTable()),
  tyvekMPT(new G4MaterialPropertiesTable()),
  linerMPT(new G4MaterialPropertiesTable()),
  HDPE(nullptr)
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
  
void WCG4DetectorConstruction::DefineElements() {
  G4String name, symbol;
  G4int z;

  elC = new G4Element(name = "Carbon", symbol = "C", z = 6, 12.0107*g/mole);
  elH = new G4Element(name = "Hydrogen", symbol = "H", z = 1, 1.01*g/mole);
  elO = new G4Element(name = "Oxygen", symbol = "O", z = 8, 15.9994*g/mole);
}

void WCG4DetectorConstruction::ConstructWater() {
  G4int nel, natoms;
  G4double density=1*g/cm3;

  double waterRindex[2] = {1.33, 1.33};
  double waterRindexEbins[2] = {2.08, 4.20};

  elWater = new G4Material(name="WATER", density, nel=3);
  elWater->AddElement(elH, natoms=2);
  elWater->AddElement(elO, natoms=1);

  waterMPT->AddProperty("RINDEX", waterRindexEbins, waterRindex,2);
  waterMPT->AddProperty("ABSLENGTH", eBins, absLength,30);

  elWater->SetMaterialPropertiesTable(waterMPT);

}

void WCG4DetectorConstruction::ConstructHDPE() {
  G4double density= 0.943*g/cm3;
  G4int nel, natoms;
  G4string name;

  HDPE = new G4Material(name="HDPE", density, nel=2);
  HDPE->AddElement(elC, natoms=2);
  HDPE->AddElement(elH, natoms=4);

  linerMPT->AddProperty("ABSLENGTH", eBins, tyvekReflectivity,30); 

  HDPE->SetMaterialPropertiesTable(linerMPT);

  return;
}

void WCG4DetectorConstruction::ConstructLinerOpSurface() {
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
  LinerOpSurface->SetFinish(groundbackpainted);
  LinerOpSurface->SetSigmaAlpha(SigmaAlpha);
  LinerOpSurface->SetMaterialPropertiesTable(linerMPT);
}

//Is scoring volume set to the correct thing?
G4VPhysicalVolume* WCG4DetectorConstruction::Construct()
{

  //dimensions:
  worlddim=1.0*m;
  tankRadius=1.8*m;
  tankHeight=1.2*m;
  wallThickness=1.22*cm;

  //G4NistManager* man = G4NistManager::Instance();
  //G4Material* Water = man->FindOrBuildMaterial("G4_WATER");
  //Water->SetMaterialPropertiesTable(waterMPT);
  //G4Material* Polyethylene = man->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Vacuum = new G4Material("Vacuum",1., 1.101*g/mole, 1.e-9*g/cm3, kStateGas,0.1*kelvin, 1.e-19*pascal);

  //create shapes:
  worldBox = new G4Box("World", 2*worlddim, 2*worlddim, worlddim);
  Tank = new G4Tubs("Tank", 0,  tankRadius, tankHeight/2, 0.*deg, 360.*deg); 
  Sidewalls = new G4Tubs("Sidewalls",tankRadius, tankRadius+wallThickness, tankHeight/2, 0.*deg, 360.*deg);
  Topwalls = new G4Tubs("Topwalls",0, tankRadius+wallThickness, wallThickness/2, 0.*deg, 360.*deg);
  Bottomwalls = new G4Tubs("Bottomwalls",0, tankRadius+wallThickness, wallThickness/2, 0.*deg, 360.*deg);

  //Next, create logical volumes by matching the shapes with materials
  logWorld = new G4LogicalVolume(worldBox,Vacuum, "World");
  logTank = new G4LogicalVolume(Tank, elWater, "Tank"); 
  logSidewalls = new G4LogicalVolume(Sidewalls, HDPE, "Sidewalls");  
  logTopwalls = new G4LogicalVolume(Topwalls, HDPE, "Topwalls");  
  logBottomwalls = new G4LogicalVolume(Bottomwalls, HDPE, "Bottomwalls");  

  G4ThreeVector centroid = G4ThreeVector(0,0,0);
  G4ThreeVector vTopwalls = G4ThreeVector(0,0,(tankHeight+wallThickness)/2);
  G4ThreeVector vBottomwalls = G4ThreeVector(0,0,-(tankHeight+wallThickness)/2);

  physWorld = new G4PVPlacement(nullptr,centroid, logWorld,"World", nullptr, false, 0);
  physTank = new G4PVPlacement(nullptr, centroid, logTank, "Tank", logWorld, false, 1);
  physSidewalls = new G4PVPlacement(nullptr,centroid, logSidewalls, "Sidewalls", logWorld, false, 2);
  physTopwalls = new G4PVPlacement(nullptr,vTopwalls, logTopwalls, "Topwalls", logWorld, false, 2);
  physBottomwalls = new G4PVPlacement(nullptr,vBottomwalls, logBottomwalls, "Bottomwalls", logWorld, false, 2);

  topSurface = new G4LogicalBorderSurface("topsurface", physTank, physTopwalls, LinerOpSurface);
  bottomSurface = new G4LogicalBorderSurface("bottomsurface", physTank, physBottomwalls, LinerOpSurface);
  wallSurface = new G4LogicalBorderSurface("wallsurface", physTank, physSidewalls, LinerOpSurface);

  //fScoringVolume = logTank;
  //What is this?
 
  return physWorld;
}

