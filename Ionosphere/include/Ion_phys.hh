#ifndef Ion_phys_h
#define Ion_phys_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class Ion_phys: public G4VUserPhysicsList
{
  public:
    Ion_phys();
    ~Ion_phys();

  protected:
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif







