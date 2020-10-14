#ifndef Physics_h
#define Physics_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"


class Physics: public G4VUserPhysicsList
{
  public:
    Physics();
   ~Physics();

  protected:
    void ConstructParticle();
    void ConstructProcess();
 
    void SetCuts();

   
  protected:
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();

  protected:
    void ConstructGeneral();
    void ConstructEM();
    void AddStepMax();

  private:
  
 G4double  cutForGamma;     
 G4double  cutForElectron;
};

#endif

 
