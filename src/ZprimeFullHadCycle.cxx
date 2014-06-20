// $Id: ZprimeFullHadCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/ZprimeFullHadCycle.h"


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
//   ZprimeSel = new Selection("ZprimeSel");
//   //DO NOT use trigger selection in PROOF mode at the moment
//   //TopSel->addSelectionModule(new TriggerSelection("HLT_PFJet320_v"));
//   ZprimeSel->addSelectionModule(new ZprimeFullHadSelection(1,1,1,1,0,0,0,e_CSVM,e_CSVM,0.6,0.6,1.0,200.0,200.0));
//   RegisterSelection(ZprimeSel);
  
//   hltpaths={
//   //BJetPlusX
//     "HLT_DiJet40Eta2p6_BTagIP3DFastPV_v",
//     "HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v",
//     "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v",
//     "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d03_v6",
//     "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d05_v6",
//     "HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose_v8",
//     "HLT_Jet60Eta1p7_Jet53Eta1p7_DiBTagIP3DFastPV_v8",
//     "HLT_Jet80Eta1p7_Jet70Eta1p7_DiBTagIP3DFastPV_v8",
//     "HLT_L1DoubleJet36Central_v7",
//     "HLT_QuadJet75_55_35_20_BTagIP_VBF_v9",
//     "HLT_QuadJet75_55_35_20_VBF_v2",
//     "HLT_QuadJet75_55_38_20_BTagIP_VBF_v9",
//     "HLT_QuadPFJet78_61_44_31_BTagCSV_VBF_v7",
//     "HLT_QuadPFJet78_61_44_31_VBF_v2",
//     "HLT_QuadPFJet82_65_48_35_BTagCSV_VBF_v7",
//     
//  //HTMHT
//     "HLT_HT250_AlphaT0p55_v8",
//     "HLT_HT250_AlphaT0p57_v8",
//     "HLT_HT300_AlphaT0p53_v8",
//     "HLT_HT300_AlphaT0p54_v14",
//     "HLT_HT350_AlphaT0p52_v8",
//     "HLT_HT350_AlphaT0p53_v19",
//     "HLT_HT400_AlphaT0p51_v19",
//     "HLT_HT400_AlphaT0p52_v14",
//     "HLT_HT450_AlphaT0p51_v14",
//     "HLT_PFNoPUHT350_PFMET100_v5",
//     "HLT_PFNoPUHT400_PFMET100_v5",
//     "HLT_RsqMR40_Rsq0p04_v6",
//     "HLT_RsqMR55_Rsq0p09_MR150_v6",
//     "HLT_RsqMR60_Rsq0p09_MR150_v6",
//     "HLT_RsqMR65_Rsq0p09_MR150_v5",
//     
// //HTMHTParked
//     "HLT_HT200_AlphaT0p57_v8",
//     "HLT_HT250_AlphaT0p55_v8",
//     "HLT_HT250_AlphaT0p57_v8",
//     "HLT_HT300_AlphaT0p53_v8",
//     "HLT_HT300_AlphaT0p54_v14",
//     "HLT_HT350_AlphaT0p52_v8",
//     "HLT_HT350_AlphaT0p53_v19",
//     "HLT_HT400_AlphaT0p51_v19",
//     "HLT_HT400_AlphaT0p52_v14",
//     "HLT_HT450_AlphaT0p51_v14",
//     "HLT_PFNoPUHT350_PFMET100_v5",
//     "HLT_PFNoPUHT400_PFMET100_v5",
//     "HLT_RsqMR40_Rsq0p04_v6",
//     "HLT_RsqMR45_Rsq0p09_v5",
//     "HLT_RsqMR55_Rsq0p09_MR150_v6",
//     "HLT_RsqMR60_Rsq0p09_MR150_v6",
//     "HLT_RsqMR65_Rsq0p09_MR150_v5",
//     
// //JetHT
//     "HLT_DiPFJetAve320_v11",
//     "HLT_DiPFJetAve400_v11",
//     "HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v11",
//     "HLT_HT200_v6",
//     "HLT_HT250_v7",
//     "HLT_HT300_DoubleDisplacedPFJet60_ChgFraction10_v11",
//     "HLT_HT300_DoubleDisplacedPFJet60_v11",
//     "HLT_HT300_SingleDisplacedPFJet60_ChgFraction10_v11",
//     "HLT_HT300_SingleDisplacedPFJet60_v11",
//     "HLT_HT300_v7",
//     "HLT_HT350_v7",
//     "HLT_HT400_v7",
//     "HLT_HT450_v7",
//     "HLT_HT500_v7",
//     "HLT_HT550_v7",
//     "HLT_HT650_Track50_dEdx3p6_v11",
//     "HLT_HT650_Track60_dEdx3p7_v11",
//     "HLT_HT650_v7",
//     "HLT_HT750_v7",
//     "HLT_Jet370_NoJetID_v15",
//     "HLT_MET80_Track50_dEdx3p6_v7",
//     "HLT_MET80_Track60_dEdx3p7_v7",
//     "HLT_MET80_v5",
//     "HLT_PFJet320_v10",
//     "HLT_PFJet400_v10",
//     "HLT_PFNoPUHT350_v5",
//     "HLT_PFNoPUHT650_DiCentralPFNoPUJet80_CenPFNoPUJet40_v5",
//     "HLT_PFNoPUHT650_v5",
//     "HLT_PFNoPUHT700_v5",
//     "HLT_PFNoPUHT750_v5",
//     
// //MultiJet
//     "HLT_DiJet80_DiJet60_DiJet20_v6",
//     "HLT_DoubleJet20_ForwardBackward_v4",
//     "HLT_EightJet30_eta3p0_v5",
//     "HLT_EightJet35_eta3p0_v5",
//     "HLT_ExclDiJet35_HFAND_v4",
//     "HLT_ExclDiJet35_HFOR_v4",
//     "HLT_ExclDiJet80_HFAND_v4",
//     "HLT_QuadJet60_DiJet20_v6",
//     "HLT_QuadJet70_v6",
//     "HLT_QuadJet80_v6",
//     "HLT_QuadJet90_v6",
//     "HLT_SixJet35_v6",
//     "HLT_SixJet45_v6",
//     "HLT_SixJet50_v6",
//     
// //MultiJet1Parked
//     "HLT_DiJet80_DiJet60_DiJet20_v6",
//     "HLT_DoubleJet20_ForwardBackward_v4",
//     "HLT_EightJet30_eta3p0_v5",
//     "HLT_EightJet35_eta3p0_v5",
//     "HLT_ExclDiJet35_HFAND_v4",
//     "HLT_ExclDiJet35_HFOR_v4",
//     "HLT_ExclDiJet80_HFAND_v4",
//     "HLT_QuadJet45_v1",
//     "HLT_QuadJet50_v5",
//     "HLT_QuadJet60_DiJet20_v6",
//     "HLT_QuadJet70_v6",
//     "HLT_QuadJet80_v6",
//     "HLT_QuadJet90_v6",
//     "HLT_SixJet35_v6",
//     "HLT_SixJet45_v6",
//     "HLT_SixJet50_v6"
//   }
//   
//   selection.push_back()
  
  Trigger1Sel = new Selection("Trigger1Sel");
  Trigger2Sel = new Selection("Trigger2Sel");
  Trigger3Sel = new Selection("Trigger3Sel");
  Trigger4Sel = new Selection("Trigger4Sel");
  Trigger5Sel = new Selection("Trigger5Sel");
  TriggerMu = new Selection("TriggerMu");
  TriggerHT = new Selection("TriggerHT");
  TriggerQuad = new Selection("TriggerQuad");
  Trigger650 = new Selection("Trigger650");
  Trigger300 = new Selection("Trigger300");
  Trigger1Sel->addSelectionModule(new TriggerSelection("HLT_HT750"));
  Trigger2Sel->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  Trigger3Sel->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  Trigger4Sel->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  Trigger5Sel->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  TriggerMu->addSelectionModule(new TriggerSelection("HLT_Mu40"));
  TriggerHT->addSelectionModule(new TriggerSelection("HLT_HT750"));
  TriggerQuad->addSelectionModule(new TriggerSelection("HLT_QuadJet50"));
  Trigger650->addSelectionModule(new TriggerSelection("HLT_HT650"));
  Trigger300->addSelectionModule(new TriggerSelection("HLT_HT300"));
  RegisterSelection(Trigger1Sel);
  RegisterSelection(Trigger2Sel);
  RegisterSelection(Trigger3Sel);
  RegisterSelection(Trigger4Sel);
  RegisterSelection(Trigger5Sel);
  RegisterSelection(TriggerMu);
  RegisterSelection(TriggerHT);
  RegisterSelection(TriggerQuad);
  RegisterSelection(Trigger650);
  RegisterSelection(Trigger300);
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
  RegisterHistCollection( new ZprimeFullHadHists("NoCutsHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("BaseHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("Trigger1Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("Trigger2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("Trigger3Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("Trigger4Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("Trigger5Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbaseHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHTHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuadHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFMuHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase650Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHT650Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase300Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuad300Histos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbaseBtagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHTBtagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuadBtagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase650BtagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHT650BtagHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbase300BtagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuad300BtagHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbaseBtag2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHTBtag2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuadBtag2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase650Btag2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHT650Btag2Histos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbase300Btag2Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuad300Btag2Histos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbaseBtaglHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHTBtaglHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuadBtaglHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase650BtaglHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHT650BtaglHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbase300BtaglHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuad300BtaglHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbaseBtag2lHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHTBtag2lHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuadBtag2lHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFbase650Btag2lHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFHT650Btag2lHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbase300Btag2lHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFQuad300Btag2lHistos"));
  
  RegisterHistCollection( new ZprimeFullHadHists("SFbase40Histos"));
  RegisterHistCollection( new ZprimeFullHadHists("SFMu40BtaglHistos"));
  
/*  
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2jet"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_2btl"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_2btm"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_2nsb"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_2btl_2nsb"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_2btm_2nsb"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2btm"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2btl_2nsb"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2nsb"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_1btl"));
  RegisterHistCollection( new ZprimeFullHadHists("Cat_2htt_1btm"));
  
  RegisterHistCollection( new ZprimeFullHadHists("AntitagHistos"));
  RegisterHistCollection( new ZprimeFullHadHists("MistagHistos"));*/
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
//   counter=0;
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

  BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");
  BaseHists* BaseHistos = GetHistCollection("BaseHistos");
  BaseHists* Trigger1Histos = GetHistCollection("Trigger1Histos");
  BaseHists* Trigger2Histos = GetHistCollection("Trigger2Histos");
  BaseHists* Trigger3Histos = GetHistCollection("Trigger3Histos");
  BaseHists* Trigger4Histos = GetHistCollection("Trigger4Histos");
  BaseHists* Trigger5Histos = GetHistCollection("Trigger5Histos");
  BaseHists* SFbaseHistos = GetHistCollection("SFbaseHistos");
  BaseHists* SFHTHistos = GetHistCollection("SFHTHistos");
  BaseHists* SFQuadHistos = GetHistCollection("SFQuadHistos");
  BaseHists* SFMuHistos = GetHistCollection("SFMuHistos");
  BaseHists* SFbase650Histos = GetHistCollection("SFbase650Histos");
  BaseHists* SFHT650Histos = GetHistCollection("SFHT650Histos");
  BaseHists* SFbase300Histos = GetHistCollection("SFbase300Histos");
  BaseHists* SFQuad300Histos = GetHistCollection("SFQuad300Histos");
  
  BaseHists* SFbaseBtagHistos = GetHistCollection("SFbaseBtagHistos");
  BaseHists* SFHTBtagHistos = GetHistCollection("SFHTBtagHistos");
  BaseHists* SFQuadBtagHistos = GetHistCollection("SFQuadBtagHistos");
  BaseHists* SFbase650BtagHistos = GetHistCollection("SFbase650BtagHistos");
  BaseHists* SFHT650BtagHistos = GetHistCollection("SFHT650BtagHistos");
  
  BaseHists* SFbase300BtagHistos = GetHistCollection("SFbase300BtagHistos");
  BaseHists* SFQuad300BtagHistos = GetHistCollection("SFQuad300BtagHistos");
  
  
  BaseHists* SFbaseBtag2Histos = GetHistCollection("SFbaseBtag2Histos");
  BaseHists* SFHTBtag2Histos = GetHistCollection("SFHTBtag2Histos");
  BaseHists* SFQuadBtag2Histos = GetHistCollection("SFQuadBtag2Histos");
  BaseHists* SFbase650Btag2Histos = GetHistCollection("SFbase650Btag2Histos");
  BaseHists* SFHT650Btag2Histos = GetHistCollection("SFHT650Btag2Histos");
  
  BaseHists* SFbase300Btag2Histos = GetHistCollection("SFbase300Btag2Histos");
  BaseHists* SFQuad300Btag2Histos = GetHistCollection("SFQuad300Btag2Histos");
  
  
  BaseHists* SFbaseBtaglHistos = GetHistCollection("SFbaseBtaglHistos");
  BaseHists* SFHTBtaglHistos = GetHistCollection("SFHTBtaglHistos");
  BaseHists* SFQuadBtaglHistos = GetHistCollection("SFQuadBtaglHistos");
  BaseHists* SFbase650BtaglHistos = GetHistCollection("SFbase650BtaglHistos");
  BaseHists* SFHT650BtaglHistos = GetHistCollection("SFHT650BtaglHistos");
  
  BaseHists* SFbase300BtaglHistos = GetHistCollection("SFbase300BtaglHistos");
  BaseHists* SFQuad300BtaglHistos = GetHistCollection("SFQuad300BtaglHistos");
  
  
  BaseHists* SFbaseBtag2lHistos = GetHistCollection("SFbaseBtag2lHistos");
  BaseHists* SFHTBtag2lHistos = GetHistCollection("SFHTBtag2lHistos");
  BaseHists* SFQuadBtag2lHistos = GetHistCollection("SFQuadBtag2lHistos");
  BaseHists* SFbase650Btag2lHistos = GetHistCollection("SFbase650Btag2lHistos");
  BaseHists* SFHT650Btag2lHistos = GetHistCollection("SFHT650Btag2lHistos");
  
  BaseHists* SFbase300Btag2lHistos = GetHistCollection("SFbase300Btag2lHistos");
  BaseHists* SFQuad300Btag2lHistos = GetHistCollection("SFQuad300Btag2lHistos");
  
  BaseHists* SFbase40Histos = GetHistCollection("SFbase40Histos");
  BaseHists* SFMu40BtaglHistos = GetHistCollection("SFMu40BtaglHistos");
  
  
  
//   BaseHists* Cat_2jetHistos = GetHistCollection("Cat_2jet");
//   BaseHists* Cat_2httHistos = GetHistCollection("Cat_2htt");
//   BaseHists* Cat_2htt_2btlHistos = GetHistCollection("Cat_2htt_2btl");
//   BaseHists* Cat_2htt_2btmHistos = GetHistCollection("Cat_2htt_2btm");
//   BaseHists* Cat_2htt_2nsbHistos = GetHistCollection("Cat_2htt_2nsb");
//   BaseHists* Cat_2htt_2btl_2nsbHistos = GetHistCollection("Cat_2htt_2btl_2nsb");
//   BaseHists* Cat_2htt_2btm_2nsbHistos = GetHistCollection("Cat_2htt_2btm_2nsb");
//   BaseHists* Cat_2btmHistos = GetHistCollection("Cat_2btm");
//   BaseHists* Cat_2btl_2nsbHistos = GetHistCollection("Cat_2btl_2nsb");
//   BaseHists* Cat_2nsbHistos = GetHistCollection("Cat_2nsb");
//   BaseHists* Cat_2htt_1btlHistos = GetHistCollection("Cat_2htt_1btl");
//   BaseHists* Cat_2htt_1btmHistos = GetHistCollection("Cat_2htt_1btm");
//   
//   BaseHists* AntitagHistos = GetHistCollection("AntitagHistos");
//   BaseHists* MistagHistos = GetHistCollection("MistagHistos");

  //if(!chi2_selection->passSelection())  throw SError( SError::SkipEvent );

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
    bool IsRealData = calc->IsRealData();
  //printTrigger(bcc);
  NoCutsHistos->Fill();
  //if (bcc->topjets->size()>=2){std::cout<<"p "<<std::endl;}

std::vector<int> Indices;  
Indices={0,1};
/*
  Indices=getTopJetsIndices(bcc,0,0,0,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2jetHistos)->Fill2(Indices);}
  else {return;}
  Indices=getTopJetsIndices(bcc,1,1,0,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2httHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,1,0,0,e_CSVL,e_CSVL,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_2btlHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,1,0,0,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_2btmHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,0,0,1,1,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_2nsbHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,1,1,1,e_CSVL,e_CSVL,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_2btl_2nsbHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,1,1,1,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_2btm_2nsbHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,0,0,1,1,0,0,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2btmHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,0,0,1,1,1,1,e_CSVL,e_CSVL,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2btl_2nsbHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,0,0,0,0,1,1,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2nsbHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,0,0,0,e_CSVL,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_1btlHistos)->Fill2(Indices);}
  Indices=getTopJetsIndices(bcc,1,1,1,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
  if (checkIndices(Indices)){
  ((ZprimeFullHadHists*)Cat_2htt_1btmHistos)->Fill2(Indices);}

  if (IsRealData)
  {
    std::vector<int> probeindex;
    Indices=getTopJetsIndices(bcc,-1,0,-1,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
    if (checkIndices(Indices))
    {
      probeindex=Indices; 
      Indices=getTopJetsIndices(bcc,-1,1,-1,1,0,0,e_CSVM,e_CSVM,0.6,200.0);
      if (checkIndices(Indices))
      {
	((ZprimeFullHadHists*)MistagHistos)->Fill2(Indices);
	((ZprimeFullHadHists*)AntitagHistos)->Fill2(Indices);
      }
      else
      {
	((ZprimeFullHadHists*)AntitagHistos)->Fill2(probeindex);
      }
    }
  }

*/
  //Indices = getTopJetsIndices(bcc,1,1,1,1,0,0,0,e_CSVM,e_CSVM,0.6,0.6,1.0,200.0,200.0);
  //if (!checkIndices(Indices)) return;//{throw SError( SError::SkipEvent ); return;}
//   int Index1=-1;int Index2=-1;double Maxpt1=-1;double Maxpt2=-1;
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     TopJet tj=bcc->toptagjets->at(i);
//     if (variableHepTopTag(tj,150.0) && subJetBTag(tj,e_CSVM)>0 && tj.pt()>150.0 && tj.pt()>Maxpt1)
//     {
//      Index1=i;
//      Maxpt1=tj.pt();
//     }
//   }
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     TopJet tj=bcc->toptagjets->at(i);
//     if (variableHepTopTag(tj,150.0) && subJetBTag(tj,e_CSVM)>0 && tj.pt()>150.0 && tj.pt()>Maxpt2 && i!=Index1)
//     {
//      Index2=i;
//      Maxpt2=tj.pt();
//     }
//   }
//   if (!(Index1!=-1 && Index2!=-1 && Index1!=Index2)) return;

//   bool two_matched_pt=false;
//   int n=0;
//   int nfilt=0;
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     if (bcc->toptagjets->at(i).pt()>=150.0) n++;//150
//   }
//   
//   for (unsigned int i=0; i<bcc->topjets->size(); i++)
//   {
//     if ( HepTopTagMatchPt(bcc->topjets->at(i))>=150.0 ) nfilt++;//150
//   }
//   
//   if (bcc->topjets->size()>1)
//   {
//     if ( ( HepTopTagMatchPt(bcc->topjets->at(0))>=150.0 ) && ( HepTopTagMatchPt(bcc->topjets->at(1))>=150.0 ) ) two_matched_pt=true;
//   }
//   







  bool HT_trigger = TriggerHT->passSelection();
  bool Quad_trigger = TriggerQuad->passSelection();
  bool Mu_trigger = TriggerMu->passSelection();
  bool HT650_trigger = Trigger650->passSelection();
  bool HT300_trigger = Trigger300->passSelection();
  
  bool signal_region = false;
  bool ncsvm = 0;
  bool ncsvl = 0;
  if (bcc->topjets->size()>1)
  {
    if(HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1))) signal_region=true;
    if (subJetBTag(bcc->topjets->at(0),e_CSVM)>0) ncsvm++;
    if (subJetBTag(bcc->topjets->at(1),e_CSVM)>0) ncsvm++;
    if (subJetBTag(bcc->topjets->at(0),e_CSVL)>0) ncsvl++;
    if (subJetBTag(bcc->topjets->at(1),e_CSVL)>0) ncsvl++;
  }
  
  if (Mu_trigger && bcc->topjets->size()>1)
  {
    if (signal_region)
    {
      ((ZprimeFullHadHists*)SFbaseHistos)->Fill2(Indices);
      if (HT_trigger)
      {
        ((ZprimeFullHadHists*)SFHTHistos)->Fill2(Indices);
      }
      if (Quad_trigger)
      {
        ((ZprimeFullHadHists*)SFQuadHistos)->Fill2(Indices);
      }
    }
  }
  
  if (HT650_trigger && signal_region)
  {
    ((ZprimeFullHadHists*)SFbase650Histos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHT650Histos)->Fill2(Indices);
    }
  }
  
  if (HT300_trigger && signal_region)
  {
    ((ZprimeFullHadHists*)SFbase300Histos)->Fill2(Indices);
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuad300Histos)->Fill2(Indices);
    }
  }
  
  
  
  
  if (Mu_trigger && signal_region && ncsvm>0)
  {
      ((ZprimeFullHadHists*)SFbaseBtagHistos)->Fill2(Indices);
      if (HT_trigger)
      {
        ((ZprimeFullHadHists*)SFHTBtagHistos)->Fill2(Indices);
      }
      if (Quad_trigger)
      {
        ((ZprimeFullHadHists*)SFQuadBtagHistos)->Fill2(Indices);
      }
  }
  
  if (HT650_trigger && signal_region && ncsvm>0)
  {
    ((ZprimeFullHadHists*)SFbase650BtagHistos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHT650BtagHistos)->Fill2(Indices);
    }
  }
  
  if (HT300_trigger && signal_region && ncsvm>0)
  {
    ((ZprimeFullHadHists*)SFbase300BtagHistos)->Fill2(Indices);
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuad300BtagHistos)->Fill2(Indices);
    }
  }
  
  
  
  
  
  if (Mu_trigger && signal_region && ncsvm>1)
  {
    ((ZprimeFullHadHists*)SFbaseBtag2Histos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHTBtag2Histos)->Fill2(Indices);
    }
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuadBtag2Histos)->Fill2(Indices);
    }
  }
  
  if (HT650_trigger && signal_region && ncsvm>1)
  {
    ((ZprimeFullHadHists*)SFbase650Btag2Histos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHT650Btag2Histos)->Fill2(Indices);
    }
  }
  
  if (HT300_trigger && signal_region && ncsvm>1)
  {
    ((ZprimeFullHadHists*)SFbase300Btag2Histos)->Fill2(Indices);
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuad300Btag2Histos)->Fill2(Indices);
    }
  }
  
  
  
  
  
  
  
  if (Mu_trigger && signal_region && ncsvl>0)
  {
    ((ZprimeFullHadHists*)SFbaseBtaglHistos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHTBtaglHistos)->Fill2(Indices);
    }
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuadBtaglHistos)->Fill2(Indices);
    }
  }
  
  if (HT650_trigger && signal_region && ncsvl>0)
  {
    ((ZprimeFullHadHists*)SFbase650BtaglHistos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHT650BtaglHistos)->Fill2(Indices);
    }
  }
  
  if (HT300_trigger && signal_region && ncsvl>0)
  {
    ((ZprimeFullHadHists*)SFbase300BtaglHistos)->Fill2(Indices);
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuad300BtaglHistos)->Fill2(Indices);
    }
  }
  
  
  if (Mu_trigger && signal_region && ncsvl>1)
  {
    ((ZprimeFullHadHists*)SFbaseBtag2lHistos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHTBtag2lHistos)->Fill2(Indices);
    }
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuadBtag2lHistos)->Fill2(Indices);
    }
  }
  
  if (HT650_trigger && signal_region && ncsvl>1)
  {
    ((ZprimeFullHadHists*)SFbase650Btag2lHistos)->Fill2(Indices);
    if (HT_trigger)
    {
      ((ZprimeFullHadHists*)SFHT650Btag2lHistos)->Fill2(Indices);
    }
  }
  
  if (HT300_trigger && signal_region && ncsvl>1)
  {
    ((ZprimeFullHadHists*)SFbase300Btag2lHistos)->Fill2(Indices);
    if (Quad_trigger)
    {
      ((ZprimeFullHadHists*)SFQuad300Btag2lHistos)->Fill2(Indices);
    }
  }
  
  if ( signal_region && ncsvl>0 )
  {
    ((ZprimeFullHadHists*)SFbase40Histos)->Fill2(Indices);
    if (Mu_trigger)
    {
      ((ZprimeFullHadHists*)SFMu40BtaglHistos)->Fill2(Indices);
    }
  }
  
  
//
//    
//
   bool HT750_trigger = Trigger1Sel->passSelection();
   bool cms_signal_region = false;
   bool cms_analysis_region = false;
   if (bcc->higgstagjets->size()>1)
   {
    if (bcc->higgstagjets->at(0).pt()>=400 && bcc->higgstagjets->at(1).pt()>=400 && TopTag(bcc->higgstagjets->at(0)) && TopTag(bcc->higgstagjets->at(1)) && bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))>2.1) cms_signal_region=true;
    if (bcc->higgstagjets->at(0).pt()>=400 && bcc->higgstagjets->at(1).pt()>=400) cms_analysis_region=true;
   }
   cms_analysis_region = cms_analysis_region && HT750_trigger;
   cms_signal_region = cms_signal_region && HT750_trigger;
   

   
   bool HT_cut = getHT50(bcc)>=800;
   bool QuadJet_cut = false;
    QuadJet_cut = true;
//    if (bcc->jets->size()>3)
//    {
//      if (bcc->jets->at(4).pt()>=60) QuadJet_cut=true;
//    }
   
  bool two_matched_pt=false;
  int n=0;
  int nfilt=0;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    if (bcc->toptagjets->at(i).pt()>=200.0) n++;
  }
  
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    if ( HepTopTagMatchPt(bcc->topjets->at(i))>=200.0 ) nfilt++;
  }
  
  if (bcc->topjets->size()>1)
  {
    if ( ( HepTopTagMatchPt(bcc->topjets->at(0))>=200.0 ) && ( HepTopTagMatchPt(bcc->topjets->at(1))>=200.0 ) ) two_matched_pt=true;
  }
  
  bool good_number_of_jets = (n>1) && (nfilt==2) && (two_matched_pt);
  
  
  bool HT_region = HT750_trigger && (!cms_analysis_region) && HT_cut && good_number_of_jets;
  
  bool Quad_region =/* QuadJet50_trigger &&*/ ( !HT_region ) && ( !cms_analysis_region ) /*&& QuadJet_cut*/ && good_number_of_jets;


   bool htt_analysis_sel = good_number_of_jets;
   bool htt_signal_sel = false; 
   if (htt_analysis_sel)
   {
    if  (HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1)))
    {
      htt_signal_sel = true;
    }
   }





  if (bcc->topjets->size()>1 /*(n>1) && (nfilt==2) && (two_matched_pt)*/ )
  {
    if(HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1))&&Quad_region)
// if (HT_region)
    {


      
      ((ZprimeFullHadHists*)BaseHistos)->Fill2(Indices);
      if (Trigger1Sel->passSelection()) ((ZprimeFullHadHists*)Trigger1Histos)->Fill2(Indices);
      if (Trigger2Sel->passSelection()) ((ZprimeFullHadHists*)Trigger2Histos)->Fill2(Indices);    
      if (Trigger1Sel->passSelection() || Trigger2Sel->passSelection()) ((ZprimeFullHadHists*)Trigger3Histos)->Fill2(Indices);
    //  if (Trigger4Sel->passSelection()/*Trigger5Sel->passSelection() || Trigger2Sel->passSelection()*/) ((ZprimeFullHadHists*)Trigger4Histos)->Fill2(Indices);
    //  if (Trigger5Sel->passSelection()) ((ZprimeFullHadHists*)Trigger5Histos)->Fill2(Indices);
    }
  
 }
  
  
  if (Quad_region && htt_analysis_sel)
  {
    ((ZprimeFullHadHists*)Trigger4Histos)->Fill2(Indices);
  }
  
  if (Quad_region && htt_signal_sel)
  {
    ((ZprimeFullHadHists*)Trigger5Histos)->Fill2(Indices);
  }
  
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


