#ifndef Ion_Det_H
#define Ion_Det_H 1
class G4Box;
class G4Tubs;
class G4Sphere;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

class Ion_Det : public G4VUserDetectorConstruction
{
  public:

    Ion_Det();
    ~Ion_Det();


G4double Density[170],Height[170],oxygen_atom_con[170],oxygen_mol_con[170],Nitrogen_atom_con[170],Nitrogen_mol_con[170],Helium_con[170];
G4double Argon_con[170], Hydrogen_con[170],DenCal[170];
G4double O_Percent[170],N_Percent[170],H_Percent[170],He_Percent[170],Ar_Percent[170],Tot_Percent[170];

    G4VPhysicalVolume* Construct();

  private:
    
    G4Material *pNaI, *pBGO;     

    G4Material* Air[168];
    G4Box* Mother_Atmsop;
    G4LogicalVolume* Mother_Atmsop_log;
    G4VPhysicalVolume* Mother_Atmsop_phys;


    G4Sphere*  Layer_solid[168];
    G4LogicalVolume* Layer_lv[168];
    G4VPhysicalVolume* Layer_pv[168];
    G4ThreeVector Layer_pos[168];



    G4Tubs* pNaI_box ;
    G4LogicalVolume* pNaI_log ;
    G4VPhysicalVolume* pNaI_phys ;

    G4Tubs* pBGO1_box ;
    G4LogicalVolume* pBGO1_log ;
    G4VPhysicalVolume* pBGO1_phys ;

    G4Tubs* pBGO2_box ;
    G4LogicalVolume* pBGO2_log ;
    G4VPhysicalVolume* pBGO2_phys ;



};

#endif

