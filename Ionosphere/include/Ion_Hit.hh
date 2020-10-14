#ifndef Ion_Hit_h
#define Ion_Hit_h 1

#include "G4VHit.hh"

class Ion_Hit : public G4VHit
{
  public:

    Ion_Hit();
    ~Ion_Hit();

  public:
  
    void SetDetName  (G4String name)      { detName = name; };
    void SetEventNb  (G4int evt)          { eventNb = evt; };  
    void SetPrimaryEnergy  (G4double pE)  { pEnergy = pE; };
    void AddEdep     (G4double de)        { edep += de; };
      
    G4String GetDetName()             { return detName; };
    G4int GetEventNb()                { return eventNb; };
//    G4double GetPrimaryEnergy()       { return pEnergy; };      
    G4double GetEdep()                { return edep; };      
      
    void ClearHit()          
    {detName = ""; eventNb = -1; pEnergy = 0.; edep = 0.; };

    void Print();

  private:
  
    G4String      detName;
    G4int         eventNb;
    G4double      pEnergy;
    G4double      edep;
};

#endif
