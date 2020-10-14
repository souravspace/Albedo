#include "ActionInitialization.hh"
#include "Ion_RunAction.hh"
#include "Ion_EventAction.hh"
#include "G4UserRunAction.hh" 


ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{ }


ActionInitialization::~ActionInitialization()
{ }


void ActionInitialization::BuildForMaster() const
{

  G4UserRunAction* runaction = new Ion_RunAction ;
  SetUserAction(runaction);    
}


void ActionInitialization::Build() const
{
  Ion_RunAction* runAction = new Ion_RunAction ;
  SetUserAction(runAction);    

  Ion_EventAction* eventAction = new Ion_EventAction(runAction);
  SetUserAction(eventAction);
}  


