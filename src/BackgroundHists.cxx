#include "include/ZprimeFullHadTools.h"
#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"
#include "TH2.h"
#include <iostream>
#include <ctime>
#include "TLorentzVector.h"
#include "TRandom3.h"

using namespace std;

BackgroundHists::BackgroundHists(const char* name) : BaseHists(name)
{
  f = new TFile("/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/bkg.root");
  mistag = (TH2F*)f->Get("HEPTagger/Mistag/data_htt/Mistag_data_htt");/////////////////////////////////////////////////////////////
  shape = (TH1F*)f->Get("HEPTagger/MassShape/qcd_htt/mass_shape_qcd_htt");
}

BackgroundHists::~BackgroundHists(){
}

void BackgroundHists::Init()
{

  Book( TH1F( "Mtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  double csv_bins[] = {-1.0,0.0,0.244,0.679,1.0};
  double mistag_pt_bins[] = {200.0,210.0,220.0,230.0,240.0,250.0,260.0,270.0,280.0,290.0,300.0,310.0,320.0,330.0,340.0,350.0,360.0,370.0,380.0,390.0,400.0,410.0,430.0,450.0,500.0,600.0,800.0,1000.0,2000.0};
  Book( TH2F( "num_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins ) );
  Book( TH2F( "den_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins ) );
  //Book( TH2F( "mass_shape",";m;CSV",110,140.0,250.0,sizeof(csv_bins)/sizeof(double)-1, csv_bins));
  Book( TH1F( "mass_shape",";m;Events",110,140.0,250.0));
  
}

void BackgroundHists::Fill()
{


  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  double weight = calc->GetWeight();

  bool doMistag=false;
  bool doMassShape=false;
  bool doBackground=true;
  
  //if (!IsRealData) doBackground=False;
  
//   if (HepTopTag(bcc->toptagjets->at(0)))//tag
//   {
//    
//     //bcc->toptagjets->at(1)
//     
//   }
//   
//   for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
//   {
//     //Hist("Mtt")->Fill(getMtt(collection->at(TopJetIndices[0]),collection->at(TopJetIndices[1])),weight*htt_weight);    
//   }
//   
//   for (unsigned int i=0;i<collection->size();i++)
//   {
//     std::vector<float> csv;
//     csv=collection->at(i).btagsub_combinedSecondaryVertex();
//     float maxcsv = *max_element(std::begin(csv), std::end(csv));
//     ((TH2F*)Hist("mass_shape"))->Fill(TopJetMass(collection->at(i)),maxcsv,weight);
//   }
//   
//   std::vector<float> csv;
//   csv=collection->at(TopJetIndices[0]).btagsub_combinedSecondaryVertex();
//   float maxcsv = *max_element(std::begin(csv), std::end(csv));
//   
//   ((TH2F*)Hist("mistag"))->Fill(collection->at(TopJetIndices[1]).pt(),maxcsv,weight);//no htt reweight!!!
  
  //mistag application
  if (doBackground)
  {
    time_t timer;
    time(&timer);
    float seed=calc->GetHT()+timer;
    TRandom3 r((unsigned int)fabs(seed*sin(seed)));
    float rndm = r.Rndm();
    unsigned int tag_index;
    unsigned int mistag_index;
    if (rndm<=0.5)
    {
      tag_index=0;
      mistag_index=1;
    }
    else
    {
      tag_index=1;
      mistag_index=0;
    }
    if(HepTopTag(bcc->toptagjets->at(tag_index)) && !HepTopTag(bcc->toptagjets->at(mistag_index)))
    {
      double maxcsv=getMaxCSV(bcc->toptagjets->at(mistag_index));
      Int_t mistag_bin = mistag->FindFixBin(bcc->toptagjets->at(mistag_index).pt(),maxcsv);
      double mistag_value=mistag->GetBinContent(mistag_bin);
      TLorentzVector TagVector;
      TLorentzVector MistagVector;
      double RandomMass = shape->GetRandom();
      TagVector.SetPtEtaPhiE(bcc->toptagjets->at(tag_index).pt(),
			     bcc->toptagjets->at(tag_index).eta(),
			     bcc->toptagjets->at(tag_index).phi(),
			     bcc->toptagjets->at(tag_index).energy()
      );
      MistagVector.SetPtEtaPhiM(bcc->toptagjets->at(mistag_index).pt(),
				bcc->toptagjets->at(mistag_index).eta(),
				bcc->toptagjets->at(mistag_index).phi(),
				RandomMass
      );
      double mtt = ( TagVector + MistagVector ).M();
      int nbtags=0;
      if (subJetBTag(bcc->toptagjets->at(tag_index),e_CSVM)>0) nbtags++;
      if (subJetBTag(bcc->toptagjets->at(mistag_index),e_CSVM)>0) nbtags++;
      if (nbtags==0)
      {
	Hist("Mtt0")->Fill(mtt,mistag_value);
      }
      else
      {
	if (nbtags==1)
	{
	  Hist("Mtt1")->Fill(mtt,mistag_value);
	}
	else
	{
	  if (nbtags==2)
	  {
	    Hist("Mtt2")->Fill(mtt,mistag_value);
	  }
	}
      }
    }
  }
  //mass shape
  if (doMassShape)
  {
    int tag_index=-1;
    double max_tag_pt=-1;
    for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
    {
      if ( HepTopTag(bcc->toptagjets->at(i)) )
      {
	if (bcc->toptagjets->at(i).pt()>max_tag_pt)
	{
	  tag_index=i;
	  max_tag_pt=bcc->toptagjets->at(i).pt();
	}
      }
    }
    if (tag_index>-1)
    {
      int probe_index=-1;
      double max_probe_pt=-1;
      for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
      {
	if (bcc->toptagjets->at(i).pt()>max_probe_pt && i!=tag_index)
	{
	  probe_index=i;
	  max_probe_pt=bcc->toptagjets->at(i).pt();
	}
      }
      if (probe_index>-1)
      {
	//Indices={antitag_index,probe_index};
	// std::vector<float> csv;
	// csv=bcc->toptagjets->at(probe_index).btagsub_combinedSecondaryVertex();
	// float maxcsv = *max_element(std::begin(csv), std::end(csv));
	Hist("mass_shape")->Fill(TopJetMass(bcc->toptagjets->at(probe_index)),weight);
      }
    }
  }
  
  //mistag computation
  if (doMistag)
  {
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
	//Indices={antitag_index,probe_index};
	// std::vector<float> csv;
	// csv=bcc->toptagjets->at(probe_index).btagsub_combinedSecondaryVertex();
	// float maxcsv = *max_element(std::begin(csv), std::end(csv));
	float maxcsv = getMaxCSV(bcc->toptagjets->at(probe_index));
	((TH2F*)Hist("den_mistag"))->Fill(bcc->toptagjets->at(probe_index).pt(),maxcsv,weight);
	//((ZprimeFullHadHists*)antitag_den)->Fill2(Indices);
	if (HepTopTag(bcc->toptagjets->at(probe_index)))
	{
	  ((TH2F*)Hist("num_mistag"))->Fill(bcc->toptagjets->at(probe_index).pt(),maxcsv,weight);
	  //((ZprimeFullHadHists*)antitag_num)->Fill2(Indices);
	}
      }
    }
  }
  
  
  
}


void BackgroundHists::Finish()
{
  delete mistag;
  delete shape;
  f->Close();
  delete f;

}

