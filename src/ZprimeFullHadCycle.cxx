// $Id: ZprimeFullHadCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/ZprimeFullHadCycle.h"
#include "include/ZprimeFullHadHists.h"

#include "SFrameAnalysis/include/SelectionModules.h"
//#include "SFrameAnalysis/include/HypothesisHists.h"

ClassImp( ZprimeFullHadCycle );

ZprimeFullHadCycle::ZprimeFullHadCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

ZprimeFullHadCycle::~ZprimeFullHadCycle() 
{
  // destructor
}

void ZprimeFullHadCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void ZprimeFullHadCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void ZprimeFullHadCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------
  ZprimeSel = new Selection("ZprimeSel");
  //DO NOT use trigger selection in PROOF mode at the moment
  //TopSel->addSelectionModule(new TriggerSelection("HLT_PFJet320_v"));
  ZprimeSel->addSelectionModule(new ZprimeFullHadSelection(1,1,1,1,0,0,200.0));
  RegisterSelection(ZprimeSel);
  
  Trigger1Sel = new Selection("Trigger1Sel");
  Trigger2Sel = new Selection("Trigger2Sel");
  Trigger3Sel = new Selection("Trigger3Sel");
  Trigger4Sel = new Selection("Trigger4Sel");
  Trigger5Sel = new Selection("Trigger5Sel");
  Trigger1Sel->addSelectionModule(new TriggerSelection("HT750"));
  Trigger2Sel->addSelectionModule(new TriggerSelection("BTagMu_Jet300_Mu5"));
  Trigger3Sel->addSelectionModule(new TriggerSelection("HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose"));
  Trigger4Sel->addSelectionModule(new TriggerSelection("HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v6"));
  Trigger5Sel->addSelectionModule(new TriggerSelection("DiJet80Eta2p6_BTagIP3DFastPVLoose"));
  RegisterSelection(Trigger1Sel);
  RegisterSelection(Trigger2Sel);
  RegisterSelection(Trigger3Sel);
  RegisterSelection(Trigger4Sel);
  RegisterSelection(Trigger5Sel);
/*
  BSel = new Selection( "BSelection");
  // addSelectionModule transfers memory release responsibility to the Selection instance.
  BSel->addSelectionModule(new NBTagSelection(1)); //at least one b tag

  NoBSel = new Selection( "NoBSelection");
  NoBSel->addSelectionModule(new NBTagSelection(0,0)); //no b tags

  chi2_selection= new Selection("chi2_selection");
  Chi2Discriminator* m_chi2discr = new Chi2Discriminator();
  chi2_selection->addSelectionModule(new HypothesisDiscriminatorCut( m_chi2discr, -1*double_infinity(), 10));
  //chi2_selection->addSelectionModule(new MttbarGenCut(0,700));

  TopSel = new Selection("TopSelection");
  //DO NOT use trigger selection in PROOF mode at the moment
  //TopSel->addSelectionModule(new TriggerSelection("HLT_PFJet320_v"));
  TopSel->addSelectionModule(new NTopJetSelection(1,int_infinity(),350,2.5));
  TopSel->addSelectionModule(new NTopTagSelection(1,int_infinity()));


  // RegisterSelection transfers memory release responsibility the Selection instance to AnalysisCycle
  // (will be done in EndInputData)
  RegisterSelection(BSel);
  RegisterSelection(NoBSel);
  RegisterSelection(TopSel);
  RegisterSelection(chi2_selection);
*/
  // ---------------- set up the histogram collections --------------------
/*
  // histograms without any cuts
  RegisterHistCollection( new ZprimeFullHadHists("NoCuts") );
  RegisterHistCollection( new HypothesisHists("Chi2_NoCuts", m_chi2discr ) );

  //histograms with and without b tagging
  RegisterHistCollection( new ZprimeFullHadHists("BTag") );
  RegisterHistCollection( new ZprimeFullHadHists("NoBTag") );
  RegisterHistCollection( new HypothesisHists("Chi2_BTag", m_chi2discr ) );
  RegisterHistCollection( new HypothesisHists("Chi2_NoBTag", m_chi2discr ) );

  // histograms after the top selection
  RegisterHistCollection( new ZprimeFullHadHists("TopSel") );
  RegisterHistCollection( new HypothesisHists("Chi2_TopSel", m_chi2discr ) );
*/
  // important: initialise histogram collections after their definition
  InitHistos();

}

void ZprimeFullHadCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void ZprimeFullHadCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  counter=0;
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void ZprimeFullHadCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of ZprimeFullHadCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...
  /*BaseHists* HistsNoCuts = GetHistCollection("NoCuts");
  BaseHists* HistsBTag = GetHistCollection("BTag");
  BaseHists* HistsNoBTag = GetHistCollection("NoBTag");
  BaseHists* HistsTopSel = GetHistCollection("TopSel");
  
  BaseHists* Chi2_HistsNoCuts = GetHistCollection("Chi2_NoCuts");
  BaseHists* Chi2_HistsBTag = GetHistCollection("Chi2_BTag");
  BaseHists* Chi2_HistsNoBTag = GetHistCollection("Chi2_NoBTag");
  BaseHists* Chi2_HistsTopSel = GetHistCollection("Chi2_TopSel");*/

  //if(!chi2_selection->passSelection())  throw SError( SError::SkipEvent );

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  //if (bcc->topjets->size()>=2){std::cout<<"p "<<std::endl;}
  if (!ZprimeSel->passSelection()) return;
  //printTrigger(bcc);
 /* if(calc->GetJets()->size()>=12){
    std::cout << "run: " << calc->GetRunNum() << "   lb: " << calc->GetLumiBlock() << "  event: " << calc->GetEventNum() << "   N(jets): " << calc->GetJets()->size() << std::endl;
  }

  // start the analysis
  HistsNoCuts->Fill();
  Chi2_HistsNoCuts->Fill();

  if(BSel->passSelection()){
    HistsBTag->Fill();
    Chi2_HistsBTag->Fill();
  }
  if(NoBSel->passSelection()){
    HistsNoBTag->Fill();  
    Chi2_HistsNoBTag->Fill();
  }
  
  if(!TopSel->passSelection())  throw SError( SError::SkipEvent );

  HistsTopSel->Fill();
  Chi2_HistsTopSel->Fill();
  */  
  return;
  
}


