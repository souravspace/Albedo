#ifndef Ion_PrimaryMessenger_h
#define Ion_PrimaryMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4AnalysisMessengerHelper.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"


#include <memory>


class Ion_Primary;
class G4UICommand ;
class G4UIcmdWithADouble;
class G4ParticleGun;



class Ion_PrimaryMessenger: public G4UImessenger
{
public:
  Ion_PrimaryMessenger(Ion_Primary*, G4ParticleGun* pGun);
  ~Ion_PrimaryMessenger();

  void SetNewValue(G4UIcommand*, G4String);
  G4double height1 ;
  
  G4int  enIn;
  G4int  angle;

  
  
   
private:
  
  Ion_Primary *IonAction;
  G4ParticleGun * fParticleGun;
  G4UIcmdWithADouble*  pospolarCmd;
  G4UIcmdWithADouble*  energy_indx_Cmd ;
  
  

   
};

#endif

