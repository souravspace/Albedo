#include "Ion_Primary.hh"
#include "Ion_PrimaryMessenger.hh"
#include "Ion_Det.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include <fstream>
#include "Randomize.hh"
#include <math.h>
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


Ion_Primary::Ion_Primary()
{

G4int n_particle = 1;
particleGun = new G4ParticleGun(n_particle);

gunMessenger = new Ion_PrimaryMessenger(this, particleGun);
G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
G4ParticleDefinition* particle = particleTable->FindParticle("gamma");

particleGun->SetParticleDefinition(particle);


}


Ion_Primary::~Ion_Primary()
{
delete particleGun;
delete gunMessenger ;
}

void Ion_Primary::GeneratePrimaries(G4Event* anEvent)
{

G4double pii = 3.14159 ;


height_orig_pl = 20000.;
input_disc_radius = 7000.;
sq_r0_orig_pl = G4UniformRand()*input_disc_radius*input_disc_radius;
r0_orig_pl = sqrt (sq_r0_orig_pl) ;

phi_orig = 2*pii*G4UniformRand()  ;


z_orig = height_orig_pl*sin (ph_angle*deg) + r0_orig_pl*cos(phi_orig)*cos (ph_angle*deg) ;
y_orig = height_orig_pl*cos (ph_angle*deg) - r0_orig_pl*cos(phi_orig)*sin (ph_angle*deg) ;
x_orig = r0_orig_pl*sin(phi_orig) ;



z_dest = r0_orig_pl*cos(phi_orig)*cos (ph_angle*deg) ;
y_dest = - r0_orig_pl*cos(phi_orig)*sin (ph_angle*deg);
x_dest = r0_orig_pl*sin(phi_orig) ;




dist_origtodest_pl = sqrt (pow ((x_dest - x_orig),2.) + pow ((y_dest - y_orig),2.) + pow ((z_dest - z_orig),2.)) ;

Mx_pl = (x_dest - x_orig)/dist_origtodest_pl ;
Mz_pl = (z_dest - z_orig)/dist_origtodest_pl ;
My_pl = (y_dest - y_orig)/dist_origtodest_pl ;
 




particleGun->SetParticlePosition(G4ThreeVector(x_orig*km, y_orig*km, z_orig*km));

momentv = G4ThreeVector(Mx_pl,My_pl,Mz_pl);

particleGun->SetParticleMomentumDirection(momentv);


int en_primary[56]={5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,220,240,260,280,300,320,340,360,380,400,500,600,800,1000,3000,5000} ;




en_val = en_primary[en_indx];

particleGun->SetParticleEnergy(en_val*keV); 


particleGun->GeneratePrimaryVertex(anEvent);




}



