
#ifndef Ion_EventAction_h
#define Ion_EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class Ion_RunAction;


class Ion_EventAction : public G4UserEventAction
{
  public:
    Ion_EventAction(Ion_RunAction* runAction);
    virtual ~Ion_EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    Ion_RunAction* fRunAction;
    G4double     fEdep;

    G4int fcollectionID;
    G4int fcollectionIDA;
    
};


#endif

    
