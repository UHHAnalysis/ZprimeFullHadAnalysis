#include "include/ZprimeFullHadTools.h"
#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"
#include "TH2.h"
#include <iostream>

using namespace std;

BackgroundHists::BackgroundHists(const char* name) : BaseHists(name)
{
  f = new TFile("/afs/desy.de/users/u/usaiem/code/bkg.root","READ");
  mistag = (TH2F*)f->Get("HEPTagger/Mistag/Mistag_data_htt");
  shape = (TH2F*)f->Get("HEPTagger/MassShape/qcd_htt");
}

BackgroundHists::~BackgroundHists(){
}

void BackgroundHists::Init()
{

  Book( TH1F( "Mtt", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );

}

void BackgroundHists::Fill()
{


  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  double weight = calc->GetWeight();

  if (HepTopTag(bcc->toptagjets->at(0)))//tag
  {
   
    //bcc->toptagjets->at(1)
    
  }
  
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    //Hist("Mtt")->Fill(getMtt(collection->at(TopJetIndices[0]),collection->at(TopJetIndices[1])),weight*htt_weight);    
  }
  
}


void BackgroundHists::Finish()
{
  delete f;
  delete mistag;
  delete shape;
}

