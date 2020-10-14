#include "Ion_SteppingAC.hh"
#include "Ion_SD.hh"

#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include <strstream>
#include "Ion_Anal.hh"




#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#ifdef G4_USE_G4BESTUNIT_FOR_VERBOSE
#include "G4UnitsTable.hh"
#else
#define G4BestUnit(a,b) a
#endif




void Ion_SteppingAC::UserSteppingAction(const G4Step* pStep)
{
;
}

