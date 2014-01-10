// $Id: ZAnalysisCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/ZAnalysisCycle.h"

#include "include/ZBTagEff.h"
#include "include/HEPTopTaggerReweight.h"

#include "SFrameAnalysis/include/SelectionModules.h"
//#include "SFrameAnalysis/include/HypothesisHists.h"

ClassImp( ZAnalysisCycle );

ZAnalysisCycle::ZAnalysisCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

ZAnalysisCycle::~ZAnalysisCycle() 
{
  // destructor
}

void ZAnalysisCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void ZAnalysisCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void ZAnalysisCycle::BeginInputData( const SInputData& id ) throw( SError ) 
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
//   RegisterHistCollection( new ZprimeFullHadHists("BaseHistos"));
//   
//   RegisterHistCollection( new ZprimeFullHadHists("zerobtag"));
//   RegisterHistCollection( new ZprimeFullHadHists("onebtag"));
//   RegisterHistCollection( new ZprimeFullHadHists("twobtagloose"));
//   RegisterHistCollection( new ZprimeFullHadHists("twobtagloosensub"));
//   RegisterHistCollection( new ZprimeFullHadHists("twobtagmednsub"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_m"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_m")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_m"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_l"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_l")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_l"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_mn"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_mn")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_mn"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_ln"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_ln")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_ln"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_my"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_my")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_my"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_ly"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_ly")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_ly"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_mny"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_mny")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_mny"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_lny"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_lny")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_lny")); 
  
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_m"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_l"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_mn"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_ln"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_my"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_ly"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_mny"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_lny"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_cms"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_cms")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_cms"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_cms"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_htt"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_htt")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_htt"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_htt"));
  
  RegisterHistCollection( new ZprimeFullHadHists("had_0btag_httcms"));
  RegisterHistCollection( new ZprimeFullHadHists("had_1btag_httcms")); 
  RegisterHistCollection( new ZprimeFullHadHists("had_2btag_httcms"));
  RegisterHistCollection( new ZprimeFullHadHists("had_012btag_httcms"));
  
  RegisterHistCollection( new ZprimeFullHadHists("antitag_den"));
  RegisterHistCollection( new ZprimeFullHadHists("antitag_num"));
  RegisterHistCollection( new ZprimeFullHadHists("antitag_num_l"));
  RegisterHistCollection( new ZprimeFullHadHists("antitag_num_m"));
  RegisterHistCollection( new ZprimeFullHadHists("antitag_num_ln"));
  RegisterHistCollection( new ZprimeFullHadHists("antitag_num_mn"));
  
  //RegisterHistCollection( new ZBTagEff("BTagEff"));

  // important: initialise histogram collections after their definition
  InitHistos();

}

void ZAnalysisCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void ZAnalysisCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void ZAnalysisCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of ZAnalysisCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...


  BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");
  BaseHists* TriggerHistos = GetHistCollection("TriggerHistos");
  
  BaseHists* had_0btag_m = GetHistCollection("had_0btag_m");
  BaseHists* had_1btag_m = GetHistCollection("had_1btag_m"); 
  BaseHists* had_2btag_m = GetHistCollection("had_2btag_m");
  
  BaseHists* had_0btag_l = GetHistCollection("had_0btag_l");
  BaseHists* had_1btag_l = GetHistCollection("had_1btag_l"); 
  BaseHists* had_2btag_l = GetHistCollection("had_2btag_l");
  
  BaseHists* had_0btag_mn = GetHistCollection("had_0btag_mn");
  BaseHists* had_1btag_mn = GetHistCollection("had_1btag_mn"); 
  BaseHists* had_2btag_mn = GetHistCollection("had_2btag_mn");
  
  BaseHists* had_0btag_ln = GetHistCollection("had_0btag_ln");
  BaseHists* had_1btag_ln = GetHistCollection("had_1btag_ln"); 
  BaseHists* had_2btag_ln = GetHistCollection("had_2btag_ln");
  
  BaseHists* had_0btag_my = GetHistCollection("had_0btag_my");
  BaseHists* had_1btag_my = GetHistCollection("had_1btag_my"); 
  BaseHists* had_2btag_my = GetHistCollection("had_2btag_my");
  
  BaseHists* had_0btag_ly = GetHistCollection("had_0btag_ly");
  BaseHists* had_1btag_ly = GetHistCollection("had_1btag_ly"); 
  BaseHists* had_2btag_ly = GetHistCollection("had_2btag_ly");
  
  BaseHists* had_0btag_mny = GetHistCollection("had_0btag_mny");
  BaseHists* had_1btag_mny = GetHistCollection("had_1btag_mny"); 
  BaseHists* had_2btag_mny = GetHistCollection("had_2btag_mny");
  
  BaseHists* had_0btag_lny = GetHistCollection("had_0btag_lny");
  BaseHists* had_1btag_lny = GetHistCollection("had_1btag_lny"); 
  BaseHists* had_2btag_lny = GetHistCollection("had_2btag_lny");
  
  BaseHists* had_012btag_m = GetHistCollection("had_012btag_m");
  BaseHists* had_012btag_l = GetHistCollection("had_012btag_l");
  BaseHists* had_012btag_mn = GetHistCollection("had_012btag_mn");
  BaseHists* had_012btag_ln = GetHistCollection("had_012btag_ln");
  BaseHists* had_012btag_my = GetHistCollection("had_012btag_my");
  BaseHists* had_012btag_ly = GetHistCollection("had_012btag_ly");
  BaseHists* had_012btag_mny = GetHistCollection("had_012btag_mny");
  BaseHists* had_012btag_lny = GetHistCollection("had_012btag_lny");
  
  BaseHists* had_0btag_cms = GetHistCollection("had_0btag_cms");
  BaseHists* had_1btag_cms = GetHistCollection("had_1btag_cms"); 
  BaseHists* had_2btag_cms = GetHistCollection("had_2btag_cms");
  BaseHists* had_012btag_cms = GetHistCollection("had_012btag_cms");
  
  BaseHists* had_0btag_htt = GetHistCollection("had_0btag_htt");
  BaseHists* had_1btag_htt = GetHistCollection("had_1btag_htt"); 
  BaseHists* had_2btag_htt = GetHistCollection("had_2btag_htt");
  BaseHists* had_012btag_htt = GetHistCollection("had_012btag_htt");
  
  BaseHists* had_0btag_httcms = GetHistCollection("had_0btag_httcms");
  BaseHists* had_1btag_httcms = GetHistCollection("had_1btag_httcms"); 
  BaseHists* had_2btag_httcms = GetHistCollection("had_2btag_httcms");
  BaseHists* had_012btag_httcms = GetHistCollection("had_012btag_httcms");
  
  BaseHists* antitag_den = GetHistCollection("antitag_den");
  BaseHists* antitag_num = GetHistCollection("antitag_num");
  BaseHists* antitag_num_l = GetHistCollection("antitag_num_l");
  BaseHists* antitag_num_m = GetHistCollection("antitag_num_m");
  BaseHists* antitag_num_ln = GetHistCollection("antitag_num_ln");
  BaseHists* antitag_num_mn = GetHistCollection("antitag_num_mn");
  
//   BaseHists* BaseHistos = GetHistCollection("BaseHistos");
//   BaseHists* zerobtag = GetHistCollection("zerobtag");
//   BaseHists* onebtag = GetHistCollection("onebtag");
//   BaseHists* twobtagloose = GetHistCollection("twobtagloose");
//   BaseHists* twobtagloosensub = GetHistCollection("twobtagloosensub");
//   BaseHists* twobtagmednsub = GetHistCollection("twobtagmednsub");
  //BaseHists* BTagEff = GetHistCollection("BTagEff");

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  NoCutsHistos->Fill();
  std::vector<int> Indices;
  std::vector<int> Indices2;
  std::vector<int> Indices3;
 //printTrigger(bcc);
  //BTagEff->Fill();
  double ptcut=200.0;
  double nsubcut=0.7;
  double ycut=1.0;
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //if ((TriggerSel->passSelection()) /*&& (calc->GetHT()>1000.0)*/) TriggerHistos->Fill(); else throw SError( SError::SkipEvent );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::vector<int> btag_medium_list;
  std::vector<int> btag_loose_list;
  std::vector<bool> heptoptag_list;
  std::vector<double> nsubjettiness_list;
  
  std::vector<int> CMSbtag_medium_list;
  std::vector<bool> CMStoptag_list;
  std::vector<double> CMSnsubjettiness_list;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    heptoptag_list.push_back(HepTopTag(bcc->toptagjets->at(i)));
    btag_loose_list.push_back(subJetBTag(bcc->toptagjets->at(i),e_CSVL/*,"mean","/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZBTagEff.root"*/));
    btag_medium_list.push_back(subJetBTag(bcc->toptagjets->at(i),e_CSVM/*,"mean","/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZBTagEff.root"*/));
    nsubjettiness_list.push_back(getNsub(bcc,i));
    //cout<<subJetBTag(bcc->toptagjets->at(i),e_CSVM)<<" "<< HepTopTag(bcc->toptagjets->at(i))<<" "<< getNsub(bcc,i)<<"\n";
  }
   //cout<<"\n";
  for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
  {
    double mjet=0; int nsubjets=0; double mmin=0;
    CMSbtag_medium_list.push_back( subJetBTag(bcc->higgstagjets->at(i),e_CSVM/*,"mean","/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZBTagEff.root"*/) );
    CMStoptag_list.push_back( TopTag(bcc->higgstagjets->at(i),mjet,nsubjets,mmin) );
    CMSnsubjettiness_list.push_back( getCMSNsub(bcc,i) );
    //cout<<subJetBTag(bcc->higgstagjets->at(i),e_CSVM)<<" "<< TopTag(bcc->higgstagjets->at(i),mjet,nsubjets,mmin)<<" "<< getCMSNsub(bcc,i)<<"\n";
  }
  //cout<<"\n\n";
  
  int n=0,ncms=0;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    if (bcc->toptagjets->at(i).pt()>=200.0) n++;
  }
  for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
  {
    if ((bcc->higgstagjets->at(i).pt()>=400.0)&&TopTag(bcc->higgstagjets->at(i))) ncms++;
  }
  
  //getTopJetsIndices(bcc,0,0,0,0,0,0,0,e_CSVM,e_CSVM,0,0,0,200,200,heptoptag_list,btag_medium_list,nsubjettiness_list);
  
  if ((ncms>1)&&(TriggerHT->passSelection()))
  {
    makeCMSCategories(bcc, (ZprimeFullHadHists*)had_012btag_cms, (ZprimeFullHadHists*)had_0btag_cms, (ZprimeFullHadHists*)had_1btag_cms, (ZprimeFullHadHists*)had_2btag_cms,CMStoptag_list,CMSbtag_medium_list,CMSnsubjettiness_list);
    makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_httcms, (ZprimeFullHadHists*)had_0btag_httcms, (ZprimeFullHadHists*)had_1btag_httcms, (ZprimeFullHadHists*)had_2btag_httcms, e_CSVM, 0, 0,heptoptag_list,btag_medium_list,nsubjettiness_list);
  }
  else
  {
    if(n>1)
    {
      makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_htt, (ZprimeFullHadHists*)had_0btag_htt, (ZprimeFullHadHists*)had_1btag_htt, (ZprimeFullHadHists*)had_2btag_htt, e_CSVM, 0, 0,heptoptag_list,btag_medium_list,nsubjettiness_list);
    }
  }
  
  makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_m, (ZprimeFullHadHists*)had_0btag_m, (ZprimeFullHadHists*)had_1btag_m, (ZprimeFullHadHists*)had_2btag_m, e_CSVM, 0, 0,heptoptag_list,btag_medium_list,nsubjettiness_list);
  
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_m, (ZprimeFullHadHists*)had_0btag_m, (ZprimeFullHadHists*)had_1btag_m, (ZprimeFullHadHists*)had_2btag_m, e_CSVM, 0, 0,heptoptag_list,btag_medium_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_l, (ZprimeFullHadHists*)had_0btag_l, (ZprimeFullHadHists*)had_1btag_l, (ZprimeFullHadHists*)had_2btag_l, e_CSVL, 0, 0,heptoptag_list,btag_loose_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_mn, (ZprimeFullHadHists*)had_0btag_mn, (ZprimeFullHadHists*)had_1btag_mn, (ZprimeFullHadHists*)had_2btag_mn, e_CSVM, 1, 0,heptoptag_list,btag_medium_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_ln, (ZprimeFullHadHists*)had_0btag_ln, (ZprimeFullHadHists*)had_1btag_ln, (ZprimeFullHadHists*)had_2btag_ln, e_CSVL, 1, 0,heptoptag_list,btag_loose_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_my, (ZprimeFullHadHists*)had_0btag_my, (ZprimeFullHadHists*)had_1btag_my, (ZprimeFullHadHists*)had_2btag_my, e_CSVM, 0, 1,heptoptag_list,btag_medium_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_ly, (ZprimeFullHadHists*)had_0btag_ly, (ZprimeFullHadHists*)had_1btag_ly, (ZprimeFullHadHists*)had_2btag_ly, e_CSVL, 0, 1,heptoptag_list,btag_loose_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_mny, (ZprimeFullHadHists*)had_0btag_mny, (ZprimeFullHadHists*)had_1btag_mny, (ZprimeFullHadHists*)had_2btag_mny, e_CSVM, 1, 1,heptoptag_list,btag_medium_list,nsubjettiness_list);
//   makeCategories(bcc, (ZprimeFullHadHists*)had_012btag_lny, (ZprimeFullHadHists*)had_0btag_lny, (ZprimeFullHadHists*)had_1btag_lny, (ZprimeFullHadHists*)had_2btag_lny, e_CSVL, 1, 1,heptoptag_list,btag_loose_list,nsubjettiness_list);

//   makeCMSCategories(bcc, (ZprimeFullHadHists*)had_012btag_cms, (ZprimeFullHadHists*)had_0btag_cms, (ZprimeFullHadHists*)had_1btag_cms, (ZprimeFullHadHists*)had_2btag_cms,CMStoptag_list,CMSbtag_medium_list,CMSnsubjettiness_list);
  
  int antitag_index=-1;
  double max_antitag_pt=-1;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    if ( ( !BareHepTopTag(bcc->toptagjets->at(i)) ) && ( MassAndPtCut(bcc->toptagjets->at(i)) ) )
    {
      if (bcc->toptagjets->at(i).pt()>max_antitag_pt)
      {
        antitag_index=i;
	max_antitag_pt=bcc->toptagjets->at(i).pt();
      }
    }
  }
  if (antitag_index>-1)
  {
    int probe_index=-1;
    double max_probe_pt=-1;
    for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
    {
      if (bcc->toptagjets->at(i).pt()>max_probe_pt && i!=antitag_index)
      {
	probe_index=i;
	max_probe_pt=bcc->toptagjets->at(i).pt();
      }
    }
    if (probe_index>-1)
    {
      Indices={antitag_index,probe_index};
      ((ZprimeFullHadHists*)antitag_den)->Fill2(Indices);
      if (heptoptag_list[probe_index])
      {
	((ZprimeFullHadHists*)antitag_num)->Fill2(Indices);
      }
      if (heptoptag_list[probe_index] && btag_loose_list[probe_index]>0)
      {
	((ZprimeFullHadHists*)antitag_num_l)->Fill2(Indices);
      }
      if (heptoptag_list[probe_index] && btag_medium_list[probe_index]>0)
      {
	((ZprimeFullHadHists*)antitag_num_m)->Fill2(Indices);
      }
      if (heptoptag_list[probe_index] && btag_loose_list[probe_index]>0 && nsubjettiness_list[probe_index]<nsubcut)
      {
	((ZprimeFullHadHists*)antitag_num_ln)->Fill2(Indices);
      }
      if (heptoptag_list[probe_index] && btag_medium_list[probe_index]>0 && nsubjettiness_list[probe_index]<nsubcut)
      {
	((ZprimeFullHadHists*)antitag_num_mn)->Fill2(Indices);
      }
    }
  }
    
  
//   Indices=getTopJetsIndices(bcc,1,1,1,1,0,0,0,e_CSVM,e_CSVM,nsubcut,nsubcut,ycut,ptcut,ptcut);
//   if (checkIndices(Indices)){//2 btag cat
//   ((ZprimeFullHadHists*)had_2btag_m)->Fill2(Indices);
//   }
//   else{
//     Indices2=getTopJetsIndices(bcc,1,1,1,0,0,0,0,e_CSVM,e_CSVM,nsubcut,nsubcut,ycut,ptcut,ptcut);
//     if (checkIndices(Indices2)){//1 btag cat
//       ((ZprimeFullHadHists*)had_1btag_m)->Fill2(Indices2);
//     }
//     else{
//       Indices3=getTopJetsIndices(bcc,1,1,0,0,0,0,0,e_CSVM,e_CSVM,nsubcut,nsubcut,ycut,ptcut,ptcut);
//       if(checkIndices(Indices3)){//0 btag cat
//         ((ZprimeFullHadHists*)had_0btag_m)->Fill2(Indices3);
//       }
//     }
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,1,1,0,0,e_CSVM,e_CSVM,0.6,200.0);
//   if (checkIndices(Indices))
//   {
//     /*if(!IsRealData)
//     {
//       HEPTopTaggerReweight httreweight;
//       calc->ProduceWeight(httreweight.GetScaleWeight(Indices));
//     }*/
//     ((ZprimeFullHadHists*)BaseHistos)->Fill2(Indices);
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,0,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
//   if (checkIndices(Indices))
//   {
//     ((ZprimeFullHadHists*)zerobtag)->Fill2(Indices);
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,1,0,0,0,e_CSVM,e_CSVM,0.6,200.0);
//   if (checkIndices(Indices))
//   {
//     ((ZprimeFullHadHists*)onebtag)->Fill2(Indices);
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,1,1,0,0,e_CSVL,e_CSVL,0.6,200.0);
//   if (checkIndices(Indices))
//   {
//     ((ZprimeFullHadHists*)twobtagloose)->Fill2(Indices);
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,1,1,1,1,e_CSVL,e_CSVL,0.7,200.0);
//   if (checkIndices(Indices))
//   {
//     ((ZprimeFullHadHists*)twobtagloosensub)->Fill2(Indices);
//   }
//   
//   Indices=getTopJetsIndices(bcc,1,1,1,1,1,1,e_CSVM,e_CSVM,0.7,200.0);
//   if (checkIndices(Indices))
//   {
//     ((ZprimeFullHadHists*)twobtagmednsub)->Fill2(Indices);
//   }
  //else throw SError( SError::SkipEvent );
  
  return;
  
}


