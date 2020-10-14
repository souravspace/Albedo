#include "Ion_RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "Ion_RunMessenger.hh"
#include <math.h>
#include "Ion_Anal.hh"
#include <string> 


Ion_RunAction::Ion_RunAction()
 : G4UserRunAction(),kMaxHisto(400)
{
 fRunMessenger = new Ion_RunMessenger(this);
}


Ion_RunAction::~Ion_RunAction()
{

 delete fRunMessenger;
 
}



void Ion_RunAction::BeginOfRunAction(const G4Run*)
{

runId = G4RunManager::GetRunManager()->GetNonConstCurrentRun()->GetRunID() ;

for (int j = 0; j <10000; j++)
{
count[runId][j] = 0.0 ;
}

auto st1 = "hist_" ;
auto st2 = "deg_" ;
auto st3 = "kev.dat" ;

int en_prim[56]={5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,220,240,260,280,
300,320,340,360,380,400,500,600,800,1000,3000,5000} ;



ang_primary = histId1;

en_primary = en_prim[histId2] ;



sprintf(filename, "%s%i", st1, ang_primary);
strcat(filename, st2) ;
sprintf(filename, "%s%i", filename, en_primary);
strcat(filename, st3) ;




auto analysisManager = G4AnalysisManager::Instance();
analysisManager->SetVerboseLevel(1);
analysisManager->SetActivation(true);



}



void Ion_RunAction::EndOfRunAction(const G4Run* )
{


std::ofstream ofile_hist;
ofile_hist.open(filename, std::ios::app);

for (int jj = 0 ; jj < 10000 ; jj++)
{

ofile_hist<<jj <<"\t\t"<< count[runId][jj] <<G4endl;

}


ofile_hist.close();


}




