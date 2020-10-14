#ifndef Ion_Primary_h
#define Ion_Primary_h 1
#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"

class G4ParticleGun;
class Ion_PrimaryMessenger ;
class G4Event;

class Ion_Primary : public G4VUserPrimaryGeneratorAction
{
  public:
    Ion_Primary();
    ~Ion_Primary();

  public:


    G4int ph_angle ;
    G4int en_indx ;

    void GeneratePrimaries(G4Event* anEvent);
    void SetAngle(G4int val) { ph_angle = val; }
    void SetEnIndex(G4int val) { en_indx = val; }

   

  private:
    G4ParticleGun* particleGun;
    Ion_PrimaryMessenger* gunMessenger;
    G4int num;


    G4double  height_orig_pl ;
    G4double  input_disc_radius ;
    G4double  sq_r0_orig_pl ;
    G4double  r0_orig_pl ;

    G4double  phi_orig ;

    G4double x_orig ;
    G4double z_orig ;
    G4double y_orig ;

    G4double x_dest ;
    G4double z_dest ;
    G4double y_dest ;

    G4double dist_origtodest_pl ;

    G4double Mx_pl ;
    G4double Mz_pl ;
    G4double My_pl ;
    G4ThreeVector momentv ;

    
   
    G4int en_div;
    G4int en_remain;
    G4double en_val;


   
   


};

#endif


