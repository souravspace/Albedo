#include "Ion_PrimaryMessenger.hh"
#include "Ion_Primary.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4ParticleGun.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"
#include "Randomize.hh"

#include "G4UIparameter.hh"

#include "G4UIcommand.hh"

#include <iostream>

Ion_PrimaryMessenger::Ion_PrimaryMessenger
(Ion_Primary* IonGun, G4ParticleGun* pGun)
  :IonAction(IonGun), fParticleGun(pGun)

{

pospolarCmd = new G4UIcmdWithADouble("/gun/zenith",this);
pospolarCmd->SetGuidance("Set particle origin in polar corrdinates.");
pospolarCmd->SetParameterName("theta", true,true);



energy_indx_Cmd = new G4UIcmdWithADouble("/gun/energy_indx",this);
energy_indx_Cmd->SetGuidance("calculate kinetic energy from supplied index and set it.");
energy_indx_Cmd->SetParameterName("Energy_index",true,true);

  



}


Ion_PrimaryMessenger::~Ion_PrimaryMessenger()
{
  delete pospolarCmd;
  delete energy_indx_Cmd ;
}

void Ion_PrimaryMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{

if (command==pospolarCmd) 
{
angle = pospolarCmd->GetNewDoubleValue(newValue);
IonAction->SetAngle(angle) ;
}
else if (command==energy_indx_Cmd) 
{
enIn = energy_indx_Cmd->GetNewDoubleValue(newValue);
IonAction->SetEnIndex(enIn) ;
}

}






