#ifndef Ion_RunAction_h
#define Ion_RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include<fstream>
#include <strstream>
#include <iostream>



class G4Run;
class Ion_RunMessenger;




class Ion_RunAction : public G4UserRunAction
{
  public:
   Ion_RunAction();
  ~Ion_RunAction();

   virtual void BeginOfRunAction(const G4Run*);
   virtual void EndOfRunAction(const G4Run*);
   G4int runId ;
   G4int histId1 ;
   G4int histId2 ;
   G4int histId ;
   G4int k;
   G4int div_9;
   G4int remain_9;
   G4int en_val_9[40];
   
   G4double En_h ;

   G4int phbin ;
   G4double phmin ;
   G4double phmax ;

   G4int en_primary; 
   G4int ang_primary;
   G4int count[705][10000];

   char filename[74];
   


   G4int logbin[40];

   void AddCount(G4int val1,G4int val2 ) {count[val1][val2]++; }
   
   void SetNumphBin(G4int val) { phbin = val; }
   
   void SetMaxphBin (G4int val) { phmax = val; }
    
   
   void SetMinphBin(G4int val) { phmin = val; }

   
   void SetHistId1(G4int val) { histId1 = val; }
   
   void SetHistId2(G4int val) { histId2 = val; }

   int  GetRunId(){return runId; } 
   

   

   
    
   const G4int kMaxHisto ;




  private:
  
   Ion_RunMessenger* fRunMessenger;
};


#endif



