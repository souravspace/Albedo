#include "Ion_RunMessenger.hh"
#include "Ion_RunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4Step.hh"

Ion_RunMessenger::Ion_RunMessenger(Ion_RunAction* runAction)
 : G4UImessenger(), 
   fRunAction(runAction), 
   numphBinCmd(0),
   maxphBinCmd(0),
   minphBinCmd(0),
   histIdCmd1(0),
   histIdCmd2(0)
   
{


numphBinCmd = new G4UIcmdWithAnInteger("/run/numphbin",this);
numphBinCmd->SetGuidance("Set number of photon bins");
numphBinCmd->SetParameterName("numphbin", true,true);


maxphBinCmd = new G4UIcmdWithAnInteger("/run/maxphbin",this);
maxphBinCmd->SetGuidance("Set maximum of bin in energy of photons");
maxphBinCmd->SetParameterName("maxphbin", true,true);


minphBinCmd = new G4UIcmdWithAnInteger("/run/minphbin",this);
minphBinCmd->SetGuidance("Set minimum of bin in energy of photons");
minphBinCmd->SetParameterName("minphbin", true,true);


histIdCmd1 = new G4UIcmdWithAnInteger("/run/histid1",this);
histIdCmd1->SetGuidance("Set the first part (cooresponds to angle) of histogram id to open suitable file");
histIdCmd1->SetParameterName("hid1", true,true);

histIdCmd2 = new G4UIcmdWithAnInteger("/run/histid2",this);
histIdCmd2->SetGuidance("Set the second part (cooresponds to energy) of histogram id to open suitable file");
histIdCmd2->SetParameterName("hid2", true,true);

  
}





Ion_RunMessenger::~Ion_RunMessenger()
{
  delete numphBinCmd;
  delete maxphBinCmd;
  delete minphBinCmd;
  delete histIdCmd1; 
  delete histIdCmd2; 
}



void Ion_RunMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if (command == numphBinCmd)
  {
    fRunAction->SetNumphBin(numphBinCmd->GetNewIntValue(newValues));
  }
  else if (command == maxphBinCmd)
  {   
    fRunAction->SetMaxphBin(maxphBinCmd->GetNewIntValue(newValues));
  }
  else if (command == minphBinCmd)
  {   
    fRunAction->SetMinphBin(minphBinCmd->GetNewIntValue(newValues));
  }
  else if (command == histIdCmd1)
  {   
    fRunAction->SetHistId1(histIdCmd1->GetNewIntValue(newValues));
  }
  else if (command == histIdCmd2)
  {   
    fRunAction->SetHistId2(histIdCmd2->GetNewIntValue(newValues));
  }
    
               
  
}

   
