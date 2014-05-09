// $Id: BackgroundCycle.cxx $

#include <iostream>
#include <iostream>

using namespace std;

#include "include/BackgroundCycle.h"
#include "SFrameAnalysis/include/Cleaner.h"


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


//   RegisterHistCollection( new BackgroundHists("BaseHistos"));
  
  RegisterHistCollection( new BackgroundHists("HTDatasetHistos"));
  RegisterHistCollection( new BackgroundHists("QuadJetDatasetHistos"));
  


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




  
  BaseHists* HTDatasetHistos = GetHistCollection("HTDatasetHistos");
  BaseHists* QuadJetDatasetHistos = GetHistCollection("QuadJetDatasetHistos");
  


  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
//   Cleaner cleaner;
//     std::vector<TopJet> uncleaned_topjets;
//   for(unsigned int i=0; i<bcc->topjets->size(); ++i) {
//     uncleaned_topjets.push_back(bcc->topjets->at(i));
//   }
//  
//   if (m_sys_unc==e_subJER){
//     if (m_sys_var==e_Up) cleaner.ApplysubJERVariationUp();
//     if (m_sys_var==e_Down) cleaner.ApplysubJERVariationDown();
//   }
//  
//   if(!bcc->isRealData && bcc->topjets)
// cleaner.JetEnergyResolutionShifterSubjets();
  
  string version(id.GetVersion().Data());
  
  std::vector<TopJet> uncleaned_topjets;
  Cleaner cleaner;
  if (contains(version,"_subjer"))
  {
    
    for(unsigned int i=0; i<bcc->topjets->size(); ++i) {
      uncleaned_topjets.push_back(bcc->topjets->at(i));
    }
    
    if (m_sys_unc==e_subJER){
      if (m_sys_var==e_Up) cleaner.ApplysubJERVariationUp();
      if (m_sys_var==e_Down) cleaner.ApplysubJERVariationDown();
    }
    
    if(!bcc->isRealData && bcc->topjets)
      cleaner.JetEnergyResolutionShifterSubjets();
  }
  
  
  bool IsRealData = calc->IsRealData();

  
  bool HT750_trigger = TriggerHT->passSelection();
  bool QuadJet50_trigger = TriggerQuad->passSelection();
  
   

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
   bool QuadJet_cut = false;//true;//getHT50(bcc)>=450;//false;
//    QuadJet_cut = true;
   if (bcc->jets->size()>3)
   {
     if (bcc->jets->at(3).pt()>=70) QuadJet_cut=true;
   }
   
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
  
  bool good_number_of_jets = (n>1) && (nfilt==2) && (two_matched_pt);//bcc->topjets->size()==2 && bcc->toptagjets->size()==2 && two_matched_pt;//
  
  
  bool HT_region = HT750_trigger && (!cms_analysis_region) && HT_cut && good_number_of_jets;
  
  bool Quad_region = QuadJet50_trigger && ( !HT_region ) && ( !cms_analysis_region ) && QuadJet_cut && good_number_of_jets;
    
  
  ///////////
//   if ( version.find("TTbarPScaleUp")!=string::npos ) {calc->ProduceWeight( 0.992089 );}
//   if ( version.find("TTbarPScaleDown")!=string::npos ) {calc->ProduceWeight( 0.938204 );}
  ///////////
  
  
  if (HT_region)
  {
    ((BackgroundHists*)HTDatasetHistos)->setVersion(id.GetVersion().Data());
    ((BackgroundHists*)HTDatasetHistos)->setEventNumber(bcc->event);
    ((BackgroundHists*)HTDatasetHistos)->setRegion("HTDatasetHistos");
    HTDatasetHistos->Fill();
  }
  
  if (Quad_region)
  {
    if ( version.find("MJDATA")!=string::npos && bcc->run<194270) throw SError( SError::SkipEvent );
    if (!IsRealData) calc->ProduceWeight(0.95*13.826599/19.7);/*4.114*/
    ((BackgroundHists*)QuadJetDatasetHistos)->setVersion(id.GetVersion().Data());
    ((BackgroundHists*)QuadJetDatasetHistos)->setEventNumber(bcc->event);
    ((BackgroundHists*)QuadJetDatasetHistos)->setRegion("QuadJetDatasetHistos");
    QuadJetDatasetHistos->Fill();
  }
  
  if ( (!HT_region) && (!Quad_region) ) throw SError( SError::SkipEvent );
  

  
  if ( version.find("TTbar")!=string::npos || version.find("ZP")!=string::npos || version.find("RSG")!=string::npos/*|| version.find("DATA")!=string::npos*/)
  {
    if(HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1))) 
    {
      if (contains(version,"_subjer"))
      {
	bcc->topjets->clear();
	for(unsigned int i=0; i<uncleaned_topjets.size(); ++i) 
	{
	  bcc->topjets->push_back(uncleaned_topjets.at(i));
	}
      }
      WriteOutputTree();
      
    }
    else {throw SError( SError::SkipEvent ); } 
  }
  else throw SError( SError::SkipEvent ); 
  
  return;
}



//   if (good_number_of_jets )
//   {
//     ((BackgroundHists*)BaseHistos)->setVersion(id.GetVersion().Data());
//     BaseHistos->Fill();
// 
// 
//   } else throw SError( SError::SkipEvent );

//   BaseHists* NoCutsHistos = GetHistCollection("NoCutsHistos");
//   BaseHists* TriggerHistos = GetHistCollection("TriggerHistos");
//   BaseHists* BaseHistos = GetHistCollection("BaseHistos");
//   BaseHists* PariHistos = GetHistCollection("PariHistos");
//   BaseHists* DispariHistos = GetHistCollection("DispariHistos");
//   NoCutsHistos->Fill();
  //qui
//    if(!(TriggerHT->passSelection() || TriggerQuad->passSelection())) throw SError( SError::SkipEvent );
//  if(!TriggerHT->passSelection()) throw SError( SError::SkipEvent );
//    double mjet1=0; int nsubjets1=0; double mmin1=0;
//    double mjet2=0; int nsubjets2=0; double mmin2=0;
   
//    if (bcc->higgstagjets->size()>1)
//    {
//      if(TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1)&&TopTag(bcc->higgstagjets->at(1),mjet2,nsubjets2,mmin2)&&(bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))>2.1))
//      {
//        throw SError( SError::SkipEvent );
//      }
//    }
//    int ncms=0;
//    for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
//    {
//      if (bcc->higgstagjets->at(i).pt()>=400.0) ncms++;
//    }
//    if (ncms>1) throw SError( SError::SkipEvent );
//   int ncmstag=0;
//    if(bcc->higgstagjets->size()>1){
//      TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1);
//      TopTag(bcc->higgstagjets->at(1),mjet2,nsubjets2,mmin2);
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<bcc->higgstagjets->at(0).numberOfDaughters()<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<bcc->higgstagjets->at(1).numberOfDaughters()<<" "<<mmin2<<" "<<bcc->higgstagjets->at(1).pt()<<" "<<bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))<<"\n";}
//    
//    if(bcc->higgstagjets->size()==1)
//    {
//     TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1); 
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<bcc->higgstagjets->at(0).numberOfDaughters()<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<0<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";
//    }
//    
//    if(bcc->higgstagjets->size()==0){
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<0<<" "<<mmin1<<" "<<0<<" "<<mjet2<<" "<<0<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";}
//    
//    bcc->higgstagjets->at(0).numberOfDaughters()
//    bcc->higgstagjets->at(1).numberOfDaughters()
     
//  if(getHT50(bcc)<800.0) throw SError( SError::SkipEvent );///////////////////////////

  //    if(bcc->higgstagjets->size()>1){
//      TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1);
//      TopTag(bcc->higgstagjets->at(1),mjet2,nsubjets2,mmin2);
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<bcc->higgstagjets->at(0).numberOfDaughters()<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<bcc->higgstagjets->at(1).numberOfDaughters()<<" "<<mmin2<<" "<<bcc->higgstagjets->at(1).pt()<<" "<<bcc->higgstagjets->at(0).deltaPhi(bcc->higgstagjets->at(1))<<"\n";}
//    
//    if(bcc->higgstagjets->size()==1)
//    {
//     TopTag(bcc->higgstagjets->at(0),mjet1,nsubjets1,mmin1); 
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<bcc->higgstagjets->at(0).numberOfDaughters()<<" "<<mmin1<<" "<<bcc->higgstagjets->at(0).pt()<<" "<<mjet2<<" "<<0<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";
//    }
//    
//    if(bcc->higgstagjets->size()==0){
//    cout<<"iniziaqui "<<bcc->run<<" "<<bcc->luminosityBlock<<" "<<bcc->event<<" "<<mjet1<<" "<<0<<" "<<mmin1<<" "<<0<<" "<<mjet2<<" "<<0<<" "<<mmin2<<" "<<0<<" "<<0<<"\n";}
    
//     if (!IsRealData)
//     {
//       if (bcc->event % 2 == 0)
//       {
// 	PariHistos->Fill();
//       }
//       else
//       {
// 	DispariHistos->Fill();
//       }
//     }



