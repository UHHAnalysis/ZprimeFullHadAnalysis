// $Id: BackgroundCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/BackgroundCycle.h"


#include "SFrameAnalysis/include/SelectionModules.h"

ClassImp( BackgroundCycle );

BackgroundCycle::BackgroundCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

BackgroundCycle::~BackgroundCycle() 
{
  // destructor
}

void BackgroundCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void BackgroundCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void BackgroundCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------
  //DO NOT use trigger selection in PROOF mode at the moment
  TriggerHT = new Selection("TriggerHT");
  TriggerQuad = new Selection("TriggerQuad");
  TriggerQuad->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  TriggerHT->addSelectionModule(new TriggerSelection("HLT_HT750"));

  // ---------------- set up the histogram collections --------------------

//   RegisterHistCollection( new ZprimeFullHadHists("NoCutsHistos"));
//   RegisterHistCollection( new ZprimeFullHadHists("TriggerHistos"));
  RegisterHistCollection( new BackgroundHists("BaseHistos"));
//   RegisterHistCollection( new BackgroundHists("PariHistos"));
//   RegisterHistCollection( new BackgroundHists("DispariHistos"));

  // important: initialise histogram collections after their definition
  InitHistos();

}

void BackgroundCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void BackgroundCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void BackgroundCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{

  AnalysisCycle::ExecuteEvent( id, weight );



//   BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");
//   BaseHists* TriggerHistos = GetHistCollection("TriggerHistos");
  BaseHists* BaseHistos = GetHistCollection("BaseHistos");
//   BaseHists* PariHistos = GetHistCollection("PariHistos");
//   BaseHists* DispariHistos = GetHistCollection("DispariHistos");

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
//   NoCutsHistos->Fill();
  
   if(!(TriggerHT->passSelection() /*|| TriggerQuad->passSelection()*/)) throw SError( SError::SkipEvent );
//  if(!TriggerHT->passSelection()) throw SError( SError::SkipEvent );
   
   double mjet1=0; int nsubjets1=0; double mmin1=0;
   double mjet2=0; int nsubjets2=0; double mmin2=0;
   
   if (bcc->higgstagjets->size()>1)
   {
     if(TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1)&&TopTag(bcc->higgstagjets->at(1),mjet2,nsubjets2,mmin2)&&(bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))>2.1))
     {
       throw SError( SError::SkipEvent );
     }
   }
   
   if(bcc->higgstagjets->size()>1)
   cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<nsubjets1<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<nsubjets2<<" "<<mmin2<<" "<<bcc->higgstagjets->at(1).pt()<<" "<<bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))<<"\n";
   
   if(bcc->higgstagjets->size()==1)
   cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<nsubjets1<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<nsubjets2<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";
   
   if(bcc->higgstagjets->size()==0)
   cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<nsubjets1<<" "<<mmin1<<" "<<0<<" "<<mjet2<<" "<<nsubjets2<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";
     
//   if(getHT50(bcc)<800.0) throw SError( SError::SkipEvent );///////////////////////////
//   bool two_matched_pt=false;
//   int n=0;
//   int nfilt=0;
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     if (bcc->toptagjets->at(i).pt()>=200.0) n++;//150
//   }
//   
//   for (unsigned int i=0; i<bcc->topjets->size(); i++)
//   {
//     if ( HepTopTagMatchPt(bcc->topjets->at(i))>=200.0 ) nfilt++;//150
//   }
//   
//   if (bcc->topjets->size()>1)
//   {
//     if ( ( HepTopTagMatchPt(bcc->topjets->at(0))>=200.0 ) && ( HepTopTagMatchPt(bcc->topjets->at(1))>=200.0 ) ) two_matched_pt=true;
//   }
//   
//   if ( (n>1) && (nfilt==2) && (two_matched_pt) )
//   {
//     ((BackgroundHists*)BaseHistos)->setVersion(id.GetVersion().Data());
//     BaseHistos->Fill();
//     
// //     if (!IsRealData)
// //     {
// //       if (bcc->event % 2 == 0)
// //       {
// // 	PariHistos->Fill();
// //       }
// //       else
// //       {
// // 	DispariHistos->Fill();
// //       }
// //     }
//   }
  
  
  
//   else throw SError( SError::SkipEvent );
  
//   WriteOutputTree();
  
  return;
  
}


