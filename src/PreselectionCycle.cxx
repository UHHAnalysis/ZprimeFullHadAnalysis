// $Id: PreselectionCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/PreselectionCycle.h"


#include "SFrameAnalysis/include/SelectionModules.h"
//#include "SFrameAnalysis/include/HypothesisHists.h"

ClassImp( PreselectionCycle );

PreselectionCycle::PreselectionCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

PreselectionCycle::~PreselectionCycle() 
{
  // destructor
}

void PreselectionCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void PreselectionCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void PreselectionCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------
  //DO NOT use trigger selection in PROOF mode at the moment
  //TopSel->addSelectionModule(new TriggerSelection("HLT_PFJet320_v"));
  TriggerHT = new Selection("TriggerHT");
  TriggerQuad = new Selection("TriggerQuad");
  TriggerQuad->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  TriggerHT->addSelectionModule(new TriggerSelection("HLT_HT750"));

  // ---------------- set up the histogram collections --------------------

  RegisterHistCollection( new ZprimeFullHadHists("NoCutsHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("TriggerHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("BaseHistos"));

  // important: initialise histogram collections after their definition
  InitHistos();

}

void PreselectionCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void PreselectionCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void PreselectionCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of PreselectionCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...


  BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");
  BaseHists* TriggerHistos = GetHistCollection("TriggerHistos");
  BaseHists* BaseHistos = GetHistCollection("BaseHistos");

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  //bool IsRealData = calc->IsRealData();
  NoCutsHistos->Fill();
  
  if(TriggerHT->passSelection() || TriggerQuad->passSelection() ) TriggerHistos->Fill(); else throw SError( SError::SkipEvent );
  
  int n=0;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    if (bcc->toptagjets->at(i).pt()>=200.0) n++;
  }
  
  for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
  {
    if (bcc->higgstagjets->at(i).pt()>=400.0) n++;
  }
  
  if (n>1) BaseHistos->Fill(); else throw SError( SError::SkipEvent );
  
  
// //   if (TriggerSel->passSelection() || TriggerSel2->passSelection()) TriggerHistos->Fill(); else throw SError( SError::SkipEvent );
//   if (TriggerSel2->passSelection()) TriggerHistos->Fill(); else throw SError( SError::SkipEvent );
//   //std::vector<int> Indices;  
//   int n=0;
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     if (bcc->toptagjets->at(i).pt()>=200.0) n++;
//   }
//   if (n>1) BaseHistos->Fill(); else throw SError( SError::SkipEvent );
//   //if (TriggerSel->passSelection()) TriggerHistos->Fill(); else throw SError( SError::SkipEvent );
//   //Indices=getTopJetsIndices(bcc,0,0,0,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
//   //if (checkIndices(Indices))
//   //{
//   //  //cout<<"2ok\n";
//   //  ((ZprimeFullHadHists*)BaseHistos)->Fill2(Indices);
//   //}
//   //else throw SError( SError::SkipEvent );
  
  WriteOutputTree();
  
  return;
  
}


