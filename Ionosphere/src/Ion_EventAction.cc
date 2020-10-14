
#include "Ion_EventAction.hh"
#include "Ion_RunAction.hh"

#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "Ion_SD.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"



Ion_EventAction::Ion_EventAction(Ion_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fcollectionID(-1),
  fcollectionIDA(-1)
{

} 



Ion_EventAction::~Ion_EventAction()
{}



void Ion_EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}



void Ion_EventAction::EndOfEventAction(const G4Event* evt)
{   

G4int evtID = G4EventManager::GetEventManager()->GetNonconstCurrentEvent()
                ->GetEventID();
//G4int run_ID = G4RunManager::GetRunManager()->GetNonConstCurrentRun()->GetRunID() ;

G4int run_ID = fRunAction->GetRunId();


G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(!HCE) return;

G4SDManager* pSDMan = G4SDManager::GetSDMpointer();

//std::ofstream outtestev;
//outtestev.open("out_t.dat", std::ios::app);


fcollectionID = pSDMan->GetCollectionID("NaI_Det/edep");



G4THitsMap<G4double>* evtMap = 
                     (G4THitsMap<G4double>*)(HCE->GetHC(fcollectionID));

std::map<G4int,G4double*>::iterator itr;
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {

G4double edep = *(itr->second);


//outtestev<<evtID<<"\t\t"<<run_ID<<"\t\t"<< round(edep/keV) <<G4endl;

fRunAction->AddCount(run_ID, round(edep/keV) );

}

//outtestev.close();

}


