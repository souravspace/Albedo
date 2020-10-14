#include "Ion_SD.hh"
#include "Ion_Primary.hh"

#include "G4Step.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include <math.h>
#include<fstream>

using namespace std;


Ion_SD::Ion_SD(G4String name)
:G4VSensitiveDetector(name), newStep(false)
{ 
    pHitCol = new Ion_HitCol(name, "hitCollection");


//////////////////////////
////Calculating the spectrum

G4int i,j,k,m,n,s,p;
G4double a,elog , cntot ;
 tot = 0.;
 a=pow(10,.02);
 ofstream outfile("tink1.txt");
 for(i=50;i<=155;i++)
 {
   j=pow(a,i)*1000;
   k=pow(a,i+1)*1000;
   e[i]=0;
  
   for(m=j;m<=k;m++)
   {
    n=(m/1000);
     
   s = k-j ;

    e[i]=e[i]+(ef(n)+ef(n+1))/2000;
    elog = log10 ((e[i]/s)*1000);
    }
 // e[i]=(e[i]/s)*1000;
  outfile<<i<<"\t"<<(k-j)/1000.0<<"\t"<< e[i]<< "\t" <<elog<< "\t"<<(e[i]/s)*1000<<"\t"<<(j/1000)<<endl;
}
}



Ion_SD::~Ion_SD()
{ 
    delete pHitCol;
}

G4double Ion_SD::ef(G4double en)
{
 G4double b;
 if(en<=60)
 b=7.877*pow(en,-1.29)*exp(-en/41.13);
 else
 b= 4.32*pow(10.,-4.)*pow((en/60),-6.5) + 8.4*pow(10.,-3.)*pow((en/60),-2.58) + 4.8*pow(10.,-4.)*pow((en/60),-2.05);
 return b;
}


G4bool Ion_SD::ProcessHits(G4Step*, G4TouchableHistory*) 
{
  return true;
}



void Ion_SD::Initialize(G4HCofThisEvent*)
{
    pHit = new Ion_Hit();
	pHit->ClearHit(); newStep = true;
}


void Ion_SD::ProcessHit(const G4Step* pStep)
{
G4double edep = pStep->GetTotalEnergyDeposit();
G4int evtID = G4EventManager::GetEventManager()->GetNonconstCurrentEvent()
                ->GetEventID();
CurrentVolume = pStep->GetPreStepPoint()->GetPhysicalVolume();

   
if (newStep)
{
pHit->SetDetName(pStep->GetTrack()->GetVolume()->GetName());
pHit->SetEventNb(evtID);
//pHit->SetPrimaryEnergy(pEng);
pHit->AddEdep(edep);
newStep = false;
} else pHit->AddEdep(edep);
}


void Ion_SD::EndOfEvent(G4HCofThisEvent*)
{
pHitCol->insert(pHit);
}


float a;
void Ion_SD::WriteOutput(G4String outfile)
{
    
}



