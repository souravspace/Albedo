#include "Ion_Det.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "Ion_SD.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include <fstream>
#include <iostream>
#include "math.h"


#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"


Ion_Det::Ion_Det()
 :Mother_Atmsop(0),Mother_Atmsop_log(0),Mother_Atmsop_phys(0)
{



///////////////////////////////////////////////////////////////Nutral atmosphere parameters ///////////////////////////////////////////////
//................................................................................


std::ofstream ofilee;
ofilee.open("inpu_test2.dat", std::ios::out);


G4int im ;
for ( im = 0; im<= 168; im++) {
Height[im] = 0.0 ;
Density[im] = 0.0 ;
Argon_con[im] = 0.0 ;
Helium_con[im] = 0.0 ;
Hydrogen_con[im] = 0.0 ;
Nitrogen_atom_con[im] = 0.0 ;
Nitrogen_mol_con[im] = 0.0 ;
oxygen_atom_con[im] = 0.0 ;
oxygen_mol_con[im] = 0.0 ;
}
im = 0 ;

std::ifstream infile;
infile.open("msis_in.dat", std::ios::in);

while (!infile.eof())
{
infile>>Height[im]>>Density[im]>>Argon_con[im]>>Helium_con[im]>>Hydrogen_con[im]>>Nitrogen_atom_con[im]>>Nitrogen_mol_con[im]>>oxygen_atom_con[im]>>oxygen_mol_con[im]  ;
if (infile.eof()) break;
im++ ;
}




for (int k = 0; k<=168; k++)
{
ofilee<<Height[k]<<"\t\t"<<Density[k]<<"\t\t"<<Argon_con[k]<<"\t\t"<<Helium_con[k]<<"\t\t"<<Hydrogen_con[k]<<"\t\t"<<Nitrogen_atom_con[k]<<"\t\t"<<Nitrogen_mol_con[k]<<"\t\t"<<oxygen_atom_con[k]<<"\t\t"<<oxygen_mol_con[k]<<G4endl;
}

ofilee.close();




//////////////////////////.............................................................................


G4double  mO,mO2,mN,mN2,mH,mHe,mAr;

mO   =  26.5676E-21;
mO2  =  53.1352E-21;
mN   =  23.2587E-21;
mN2  =  46.5174E-21;
mH   =  1.6786E-21;
mHe  =  6.6467E-21;
mAr  =  66.3352E-21;


for (int ii = 0; ii<= 168; ii++) {

DenCal[ii] = mO*oxygen_atom_con[ii] + mO2*oxygen_mol_con[ii]+ mN*Nitrogen_atom_con[ii] + mN2*Nitrogen_mol_con[ii]
             +mH*Hydrogen_con[ii]+mHe*Helium_con[ii]+mAr*Argon_con[ii];

O_Percent[ii] = ((mO*oxygen_atom_con[ii]+mO2*oxygen_mol_con[ii])/DenCal[ii])*100.;
N_Percent[ii] = ((mN*Nitrogen_atom_con[ii]+mN2*Nitrogen_mol_con[ii])/DenCal[ii])*100.;
H_Percent[ii] = (mH*Hydrogen_con[ii]/DenCal[ii])*100.;
He_Percent[ii] = (mHe*Helium_con[ii]/DenCal[ii])*100.;
Ar_Percent[ii] = (mAr*Argon_con[ii]/DenCal[ii])*100.;

Tot_Percent[ii] =O_Percent[ii]+N_Percent[ii]+H_Percent[ii]+He_Percent[ii]+Ar_Percent[ii]; 
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Ion_Det::~Ion_Det()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

G4VPhysicalVolume* Ion_Det::Construct()
{

// .......................................................Materials..................................................................  

G4double a;  // atomic mass
G4double z,nel;  // atomic number

G4Element* aN = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
G4Element* aO = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
G4Element* aH = new G4Element("Hydrogen"  , "H", z=1., a= 1.00794*g/mole);
G4Element* aHe = new G4Element("Helium"  , "He", z=2., a= 4.0026*g/mole);
G4Element* aAr = new G4Element("Argon"  , "Ar", z=18., a= 39.5*g/mole);

G4NistManager* man = G4NistManager::Instance();
G4Material* Vac = man->FindOrBuildMaterial("G4_Galactic");

// .........................................................................................................................


//................................................Mother_Volume..............................................................

G4double Mother_x = 25000.*km;
G4double Mother_y = 25000.*km;
G4double Mother_z = 25000.*km;

Mother_Atmsop 
= new G4Box("Mother_Atmsop",Mother_x/2.,Mother_y/2.,Mother_z/2.);
Mother_Atmsop_log = new G4LogicalVolume(Mother_Atmsop,Vac,"Mother_Atmsop_log",0,0,0);
Mother_Atmsop_phys = new G4PVPlacement(0,G4ThreeVector(),
                                     Mother_Atmsop_log,"Mother_Atmsophere",0,false,0);

Mother_Atmsop_log->SetVisAttributes (G4VisAttributes::Invisible);

//...........................................................................................................................








//.............................................Layers..............................................................


//Common

G4double Layer_y[168],Air_density[168];

Layer_y[0] = (Height[0]+6378.1);

for (int li = 1; li<= 165; li++) {

Layer_y[li] = (Height[li]+6378.1);
Air_density[li] = DenCal[li] ;

G4cout <<li<<"\t"<< Layer_y[li]<< G4endl;

Air[li] = new G4Material("Air_li",Air_density[li]*mg/cm3, nel=5);
Air[li]->AddElement(aO, O_Percent[li]/100.);
Air[li]->AddElement(aN, N_Percent[li]/100.);
Air[li]->AddElement(aH, H_Percent[li]/100.);
Air[li]->AddElement(aHe, He_Percent[li]/100.);
Air[li]->AddElement(aAr, Ar_Percent[li]/100.);

Layer_pos[li] = G4ThreeVector(0.0*km,0.0*km,0.0*km);

Layer_solid[li] =new G4Sphere("Layer_solid",Layer_y[li-1]*km,Layer_y[li]*km,0.*deg,360.*deg,0.*deg,180.*deg );
Layer_lv[li] = new G4LogicalVolume(Layer_solid[li],Air[li],"Layer_lv",0,0,0);
Layer_pv[li] = new G4PVPlacement(0,Layer_pos[li],Layer_lv[li],"Layer_pv",Mother_Atmsop_log,false,0);
//Layer_lv[li]->SetVisAttributes (G4VisAttributes::Invisible);
}
//.................................................................................................................................

//........................................................Detectors................................................................

//----------------------------------------------Sample NaI Detector placed at certain height---------------------------------------
G4double rotateX = 112. ;
G4double rotateY = 0.0 ;
//G4double rotateZ =  20. ;


G4NistManager* man1 = G4NistManager::Instance();
pBGO = man1->FindOrBuildMaterial("G4_BGO");
pNaI = man1->FindOrBuildMaterial("G4_SODIUM_IODIDE");



G4double NaI_r = 200.;
G4double NaI_w = 10.;
G4double NaI_posy = 650+6378.1;



G4RotationMatrix*  rotateNaI=new G4RotationMatrix();
rotateNaI->rotateX((90. - rotateX)*deg);


pNaI_box= new G4Tubs("NaI_det", 0.*km, NaI_r*km, NaI_w/2.*km, 0., 360.*deg);
pNaI_log = new G4LogicalVolume(pNaI_box, pNaI, "NaI_det",0,0,0);
pNaI_phys = new G4PVPlacement(rotateNaI, G4ThreeVector(0*km,NaI_posy*km,0*km), pNaI_log, "NaI_det",Mother_Atmsop_log, false, 0);




G4double BGO1_r =  NaI_r + 2;
G4double BGO1_w = NaI_w ;
G4double posy_BGO1 = NaI_posy;

G4RotationMatrix*  rotateBGO1=new G4RotationMatrix();
rotateBGO1->rotateX((90. - rotateX)*deg);


pBGO1_box= new G4Tubs("BGO1_det", NaI_r*km, BGO1_r*km, BGO1_w/2.*km, 0., 360.*deg);
pBGO1_log = new G4LogicalVolume(pBGO1_box, pBGO, "BGO1_det",0,0,0);
pBGO1_phys = new G4PVPlacement(rotateBGO1, G4ThreeVector(0*km,posy_BGO1*km,0*km), pBGO1_log, "BGO1_det",Mother_Atmsop_log, false, 0);




/*
G4double BGO2_r = NaI_r + 2.;
G4double BGO2_w = NaI_w/2.  ;
G4double posy_BGO2 = NaI_posy - (NaI_w + BGO2_w)/2. ;

G4RotationMatrix*  rotateBGO2=new G4RotationMatrix();
rotateBGO2->rotateX((90. - rotateX)*deg);




pBGO2_box= new G4Tubs("BGO2_det", 0.*km, BGO2_r*km, BGO2_w/2.*km, 0., 360.*deg);
pBGO2_log = new G4LogicalVolume(pBGO2_box, pBGO, "BGO2_det",0,0,0);
pBGO2_phys = new G4PVPlacement(rotateBGO2, G4ThreeVector(0*km,posy_BGO2*km,0*km), pBGO2_log, "BGO2_det",Mother_Atmsop_log, false, 0);

*/



//..................................................................................................
//Visualization

G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
   G4VisAttributes * yellow= new G4VisAttributes( G4Colour(255/255. ,255/255. ,51/255. ));
   G4VisAttributes * red= new G4VisAttributes( G4Colour(255/255. , 0/255. , 0/255. ));
   G4VisAttributes * blue= new G4VisAttributes( G4Colour(0/255. , 0/255. ,  255/255. ));
   G4VisAttributes * grayc= new G4VisAttributes( G4Colour(128/255. , 128/255. ,  128/255. ));
   G4VisAttributes * lightGray= new G4VisAttributes( G4Colour(178/255. , 178/255. ,  178/255. ));
   G4VisAttributes * green= new G4VisAttributes( G4Colour(0/255. , 128/255. ,  0/255. ));
   G4VisAttributes * bottlegreen= new G4VisAttributes( G4Colour(0/255. , 128/255. ,  153/255. ));
   

   simpleBoxVisAtt->SetVisibility(true);
   yellow->SetVisibility(true);
   yellow->SetForceSolid(true);
   red->SetVisibility(true);
   red->SetForceSolid(true);
   blue->SetVisibility(true);
   blue->SetForceSolid(true);
   grayc->SetVisibility(true);
   grayc->SetForceSolid(true);
   lightGray->SetVisibility(true);
   lightGray->SetForceSolid(true);

   pBGO1_log->SetVisAttributes(yellow);
   pNaI_log->SetVisAttributes(yellow);
 //  pBGO2_log->SetVisAttributes(red);




G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector("NaI_Det");
G4SDManager::GetSDMpointer()->AddNewDetector(cryst);
G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
cryst->RegisterPrimitive(primitiv1);
pNaI_log->SetSensitiveDetector(cryst);


return Mother_Atmsop_phys;
}
