

#ifndef Ion_SD_h
#define Ion_SD_h 1

#include "G4VSensitiveDetector.hh"
#include "Ion_Hit.hh"
#include "G4THitsCollection.hh"

class G4Step;
class G4HCofThisEvent;

typedef G4THitsCollection<Ion_Hit> Ion_HitCol;



class Ion_SD : public G4VSensitiveDetector
{
  public:

    Ion_SD(G4String);
    ~Ion_SD();

	G4bool ProcessHits(G4Step*, G4TouchableHistory*); 
    void Initialize(G4HCofThisEvent*);
    void ProcessHit(const G4Step*);
    void EndOfEvent(G4HCofThisEvent*);
    void WriteOutput(G4String);
    Ion_Hit* GetHit()           { return pHit;};
    Ion_HitCol* GetHitCol()     { return pHitCol;};
   G4double  ef(G4double);
  private:

    Ion_Hit*       pHit;
    Ion_HitCol*    pHitCol;
	G4bool                 newStep;
    G4VPhysicalVolume* CurrentVolume;

   G4double e[255],tot;
};



#endif

