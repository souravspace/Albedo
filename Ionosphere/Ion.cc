//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: exampleN01.cc,v 1.6 2006/06/29 17:47:10 gunter Exp $
// GEANT4 tag $Name: geant4-09-02-patch-01 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - exampleN01
// --------------------------------------------------------------

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4SDManager.hh"
#include "Ion_RunAction.hh"
#include "Ion_SteppingAC.hh"

#include "ActionInitialization.hh"

#include "Ion_Det.hh"
#include "Ion_Physics.hh"
#include "Ion_Primary.hh"
#include "Ion_SD.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include<fstream>

#include <chrono>
#include <unistd.h>
#include<ctime>

using namespace std::chrono;



int main(int argc,char** argv)
{
  // Construct the default run manager

  steady_clock::time_point start = steady_clock::now();
  //
  G4RunManager* runManager = new G4RunManager;

  
  
    
  

  // set mandatory initialization classes
  //
  G4VUserDetectorConstruction* detector = new Ion_Det;
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new Physics;
  runManager->SetUserInitialization(physics);

  // set mandatory user action class
  //

  G4VUserActionInitialization* userinit = new ActionInitialization ;  
  runManager->SetUserInitialization(userinit);


  G4VUserPrimaryGeneratorAction* gen_action = new Ion_Primary;
  runManager->SetUserAction(gen_action);


  

  // Initialize G4 kernel




  G4UserSteppingAction* stepping_action = new Ion_SteppingAC();
  runManager->SetUserAction(stepping_action);







  //
  runManager->Initialize();


  #ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  #endif
 


  // Get the pointer to the UI manager and set verbosities

 G4UImanager * UImanager = G4UImanager::GetUIpointer();

 UImanager->ApplyCommand("/run/verbose 0");
 UImanager->ApplyCommand("/event/verbose 0");
 UImanager->ApplyCommand("/tracking/verbose 0");

  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);

    }
  else           // interactive mode : define UI session
    {
 #ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
 #ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac");
 #endif
      ui->SessionStart();
      delete ui;
 #endif


  




 #ifdef G4VIS_USE
      delete visManager;
 #endif
    }

  
   ((Ion_SD*)G4SDManager::GetSDMpointer()
           ->FindSensitiveDetector("NaI"))->WriteOutput("Det_hit_Ion_85deg3.dat");


   // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  

  delete runManager;

  steady_clock::time_point end = steady_clock::now();

  duration<double> time_span = duration_cast<duration<double> >(end-start);
 


  G4cout<< "Total time taken is "<< time_span.count() << "Sec"<< G4endl;

  return 0;


}






/*
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  // Start a run
  //
  G4int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);

  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;

  return 0;
}

*/
