#ifndef Ion_SteppingAC_h
#define Ion_SteppingAC_h 1

#include "globals.hh"                 // Include from 'global'
#include <vector>


#include "G4UserSteppingAction.hh"
#include "G4VPhysicalVolume.hh"


class G4ProcessVector;
class Ion_SteppingAC : public G4UserSteppingAction
{

public:

    Ion_SteppingAC(){};
    ~Ion_SteppingAC(){};

    void UserSteppingAction(const G4Step*);
 
G4int Num_sec;
G4int runID ;
G4int evtID ;
G4int fileindex ;
G4int energybinNo ;
G4double verticlePos ;
G4int secNumber;



G4int fN2ndariesAtRestDoIt;

G4VPhysicalVolume* CurrentVolume;

};

#endif
