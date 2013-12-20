// $Id: RocCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/RocCycle.h"
#include "include/RocHists.h"

#include "SFrameAnalysis/include/SelectionModules.h"
//#include "SFrameAnalysis/include/HypothesisHists.h"

ClassImp( RocCycle );

RocCycle::RocCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

RocCycle::~RocCycle() 
{
  // destructor
}

void RocCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void RocCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void RocCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------
  //DO NOT use trigger selection in PROOF mode at the moment
  //TopSel->addSelectionModule(new TriggerSelection("HLT_PFJet320_v"));
  //TriggerSel = new Selection("TriggerSel");
  //TriggerSel->addSelectionModule(new TriggerSelection("HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose"));

  // ---------------- set up the histogram collections --------------------

  RegisterHistCollection( new RocHists("NoCutsHistos"));

  // important: initialise histogram collections after their definition
  InitHistos();

}

void RocCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void RocCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void RocCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of RocCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...


  BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  ((RocHists*)NoCutsHistos)->SetIdVersion(id.GetVersion());
  NoCutsHistos->Fill();
  
  return;
  
}


