#ifndef Ion_RunMessenger_h
#define Ion_RunMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"


class Ion_RunAction;
class Ion_SteppingAC;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;



class Ion_RunMessenger: public G4UImessenger
{
  public:
   Ion_RunMessenger(Ion_RunAction* runAction);
   ~Ion_RunMessenger();

   virtual void SetNewValue(G4UIcommand* ,G4String );

  private:
   Ion_RunAction*         fRunAction;
  

  G4UIcmdWithAnInteger*   numphBinCmd;
  G4UIcmdWithAnInteger*   maxphBinCmd;
  G4UIcmdWithAnInteger*   minphBinCmd;
  G4UIcmdWithAnInteger*   histIdCmd1;
  G4UIcmdWithAnInteger*   histIdCmd2;

  G4double angle;
  



      
};

#endif

