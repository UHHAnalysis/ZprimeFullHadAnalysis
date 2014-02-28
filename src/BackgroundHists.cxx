#include "include/ZprimeFullHadTools.h"
#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"
#include "TH2.h"
#include "TProfile2D.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TRandom3.h"

using namespace std;

BackgroundHists::BackgroundHists(const char* name) : BaseHists(name)
{
  f = new TFile("/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/bkg.root");
  //   f_pari = new TFile("/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/bkg_pari.root");
  //   f_dispari = new TFile("/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/bkg_dispari.root");
  //   mistag = (TH2F*)f_dispari->Get("HEPTagger/Mistag/qcd_htt/Mistag_qcd_htt");/////////////////////////////////////////////////////////////
  //   shape = (TH1F*)f_pari->Get("HEPTagger/MassShape/qcd_htt/mass_shape_qcd_htt");
  mistag = (TH2F*)f->Get("HEPTagger/Mistag/data_htt/Mistag_data_htt");
  mistagmc = (TH2F*)f->Get("HEPTagger/Mistag/qcd500to1000/Mistag_qcd500to1000");/////////////////////////////////////////////////////////////
  shape = (TH1F*)f->Get("HEPTagger/MassShape/qcd_htt/mass_shape_qcd_htt");
}

BackgroundHists::~BackgroundHists(){
}

void BackgroundHists::Init()
{
  
  Book( TH1F( "Mtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MttNoMass0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MttNoMass1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MttNoMass2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MttNoMass012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredJECMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredJECMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredJECMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredJECMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredHTTMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredHTTJECMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTJECMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTJECMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredHTTJECMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredAK5Mtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredAK5Mtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredAK5Mtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredAK5Mtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "Mtt012NoWeight", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "CSV012", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "HT012", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "pT012", ";pT;Events", 100, 0, 2000 ) );
  
  Book( TH1F( "CSV012", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredCSV012", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "HTTCSV012", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredHTTCSV012", ";CSV;Events", 260, -11, 2 ) );
  
  Book( TH1F( "HT012", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHT012", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "HTTHT012", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHTTHT012", ";HT;Events", 300, 0, 6000 ) );
  
  Book( TH1F( "pT012", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredpT012", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "HTTpT012", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredHTTpT012", ";pT;Events", 100, 0, 2000 ) );
  
  
  
  Book( TH1F( "CSV0", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredCSV0", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "HTTCSV0", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredHTTCSV0", ";CSV;Events", 260, -11, 2 ) );
  
  Book( TH1F( "HT0", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHT0", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "HTTHT0", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHTTHT0", ";HT;Events", 300, 0, 6000 ) );
  
  Book( TH1F( "pT0", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredpT0", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "HTTpT0", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredHTTpT0", ";pT;Events", 100, 0, 2000 ) );
  
  
  
  Book( TH1F( "CSV1", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredCSV1", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "HTTCSV1", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredHTTCSV1", ";CSV;Events", 260, -11, 2 ) );
  
  Book( TH1F( "HT1", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHT1", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "HTTHT1", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHTTHT1", ";HT;Events", 300, 0, 6000 ) );
  
  Book( TH1F( "pT1", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredpT1", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "HTTpT1", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredHTTpT1", ";pT;Events", 100, 0, 2000 ) );
  
  
  
  Book( TH1F( "CSV2", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredCSV2", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "HTTCSV2", ";CSV;Events", 260, -11, 2 ) );
  Book( TH1F( "MeasuredHTTCSV2", ";CSV;Events", 260, -11, 2 ) );
  
  Book( TH1F( "HT2", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHT2", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "HTTHT2", ";HT;Events", 300, 0, 6000 ) );
  Book( TH1F( "MeasuredHTTHT2", ";HT;Events", 300, 0, 6000 ) );
  
  Book( TH1F( "pT2", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredpT2", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "HTTpT2", ";pT;Events", 100, 0, 2000 ) );
  Book( TH1F( "MeasuredHTTpT2", ";pT;Events", 100, 0, 2000 ) );
  
  //   Book( TH1F( "fake_mass",";m;Events",110,140.0,250.0));
  double csv_bins[] = {-100.0,0.0,0.244,0.679,10.0};
  double mistag_pt_bins[] = {150.0,160.0,170.0,180.0,190.0,200.0,210.0,220.0,230.0,240.0,250.0,260.0,270.0,280.0,290.0,300.0,310.0,320.0,330.0,340.0,350.0,360.0,370.0,380.0,390.0,400.0,410.0,430.0,450.0,500.0,600.0,800.0,1000.0,2000.0};
  Book( TH2F( "num_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins ) );
  Book( TH2F( "den_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins ) );
  Book( TProfile2D( "mistag_crosscheck", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins ) );
  //   Book( TH2F( "mass_shape2D",";m;CSV",110,140.0,250.0,sizeof(csv_bins)/sizeof(double)-1, csv_bins));
  Book( TH1F( "mass_shape",";m;Events",110,140.0,250.0));
  //   Book( TH1F( "mass_shapeJEC",";m;Events",110,140.0,250.0));
  
}

void BackgroundHists::Fill()
{
  
  
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  double weight = calc->GetWeight();
  
  bool doMistag=true;
  bool doMassShape=true;
  bool doBackground=true;
  bool doMeasured=true;
  
  //if (!IsRealData) doBackground=False;
  
  //   if (HepTopTagWithMatch(bcc->topjets->at(0)))//tag
  //   {
  //
  //     //bcc->topjets->at(1)
  //
  //   }
  //
  //   for (unsigned int i=0; i<bcc->topjets->size(); i++)
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
    
    double etaseed = bcc->topjets->at(0).subjets().at(0).eta();
    int seed = abs(static_cast<int>(sin(etaseed*1000000)*100000));
    
    TRandom3 rand(seed);
    float coin = rand.Uniform(1.);
    
    unsigned int tag_index;
    unsigned int mistag_index;
    //          cout<<coin<<endl;
    if (coin<=0.5)
    {
      tag_index=0;
      mistag_index=1;
    }
    else
    {
      tag_index=1;
      mistag_index=0;
    }
    //      cout<<tag_index<<endl;
    if(HepTopTagWithMatch(bcc->topjets->at(tag_index)) /*&& !HepTopTagWithMatch(bcc->topjets->at(mistag_index))*/)
    {
      double maxcsv=getMaxCSV(bcc->topjets->at(mistag_index));
      //        cout<<bcc->topjets->at(mistag_index).pt()<<" "<<maxcsv<<endl;
      Int_t mistag_bin = 0;
      double mistag_value = 0;
      if (IsRealData)
      {
        mistag_bin = mistag->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
        mistag_value=mistag->GetBinContent(mistag_bin);
      }
      else
      {
        mistag_bin = mistagmc->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
        Int_t binx=0;
        Int_t biny=0;
        Int_t binz=0;
        mistagmc->GetBinXYZ(mistag_bin, binx, biny, binz);
        mistag_value=mistagmc->GetBinContent(mistag_bin);
        Int_t aa=((TProfile2D*)Hist("mistag_crosscheck"))->Fill(bcc->topjets->at(mistag_index).pt(),maxcsv,mistag_value);
        //cout<<maxcsv<<" "<<mistag_bin<<" "<<binx<<" "<<biny<<" "<<binz<<" "<<bcc->topjets->at(mistag_index).pt()<<" "<<aa<<"\n";
        
        
      }
      //        cout<<mistag_bin<<endl;
      TLorentzVector TagVector;
      TLorentzVector MistagVector;
      //        cout<<gRandom->ClassName()<<endl;
      
      double etaseed2 = bcc->topjets->at(1).subjets().at(0).eta();
      int seed2 = abs(static_cast<int>(sin(etaseed2*1000000)*100000));
      gRandom->SetSeed(seed2);
      double RandomMass = shape->GetRandom();
      //       Hist("fake_mass")->Fill(RandomMass,weight);
      //       cout<<RandomMass<<endl;
      
      LorentzVector TagSumOfSubjets(0,0,0,0);
      LorentzVector MistagSumOfSubjets(0,0,0,0);
      for(int j=0; j<bcc->topjets->at(tag_index).numberOfDaughters(); ++j)
      {
        TagSumOfSubjets += bcc->topjets->at(tag_index).subjets()[j].v4();
      }
      for(int j=0; j<bcc->topjets->at(mistag_index).numberOfDaughters(); ++j)
      {
        MistagSumOfSubjets += bcc->topjets->at(mistag_index).subjets()[j].v4();
      }
      
      TagVector.SetPtEtaPhiE(TagSumOfSubjets.Pt(),
                             TagSumOfSubjets.Eta(),
                             TagSumOfSubjets.Phi(),
                             TagSumOfSubjets.E()
                             );
      MistagVector.SetPtEtaPhiM(MistagSumOfSubjets.Pt(),
                                MistagSumOfSubjets.Eta(),
                                MistagSumOfSubjets.Phi(),
                                RandomMass
                                );
      //       double mtt = ( TagVector + MistagVector ).M();
      //       TagVector.SetPtEtaPhiE(bcc->topjets->at(tag_index).pt(),//old mass modification procedure
      // 			     bcc->topjets->at(tag_index).eta(),
      // 			     bcc->topjets->at(tag_index).phi(),
      // 			     bcc->topjets->at(tag_index).energy()
      //       );
      //       MistagVector.SetPtEtaPhiM(bcc->topjets->at(mistag_index).pt(),
      // 				bcc->topjets->at(mistag_index).eta(),
      // 				bcc->topjets->at(mistag_index).phi(),
      // 				RandomMass
      //       );
      double mtt = ( TagVector + MistagVector ).M();
      double mttNoMass=getMtt(bcc->topjets->at(0),bcc->topjets->at(1));//NO random mass modification
      int nbtags=0;
      if (subJetBTag(bcc->topjets->at(tag_index),e_CSVM)>0) nbtags++;
      if (subJetBTag(bcc->topjets->at(mistag_index),e_CSVM)>0) nbtags++;
      Hist("Mtt012")->Fill(mtt,mistag_value*weight);
      Hist("MttNoMass012")->Fill(mttNoMass,mistag_value*weight);
      Hist("HT012")->Fill(getHT50(bcc),mistag_value*weight);
      Hist("pT012")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
      Hist("CSV012")->Fill(getMaxCSV(bcc->topjets->at(mistag_index)),mistag_value*weight);
      if (nbtags==0)
      {
        Hist("Mtt0")->Fill(mtt,mistag_value*weight);
        Hist("MttNoMass0")->Fill(mttNoMass,mistag_value*weight);
        Hist("HT0")->Fill(getHT50(bcc),mistag_value*weight);
        Hist("pT0")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
        Hist("CSV0")->Fill(getMaxCSV(bcc->topjets->at(mistag_index)),mistag_value*weight);
      }
      else
      {
        if (nbtags==1)
        {
          Hist("Mtt1")->Fill(mtt,mistag_value*weight);
          Hist("MttNoMass1")->Fill(mttNoMass,mistag_value*weight);
          Hist("HT1")->Fill(getHT50(bcc),mistag_value*weight);
          Hist("pT1")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
          Hist("CSV1")->Fill(getMaxCSV(bcc->topjets->at(mistag_index)),mistag_value*weight);
        }
        else
        {
          if (nbtags==2)
          {
            Hist("Mtt2")->Fill(mtt,mistag_value*weight);
            Hist("MttNoMass2")->Fill(mttNoMass,mistag_value*weight);
            Hist("HT2")->Fill(getHT50(bcc),mistag_value*weight);
            Hist("pT2")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
            Hist("CSV2")->Fill(getMaxCSV(bcc->topjets->at(mistag_index)),mistag_value*weight);
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
    for (unsigned int i=0; i<bcc->topjets->size(); i++)
    {
      if ( HepTopTagWithMatch(bcc->topjets->at(i)) )
      {
        if (bcc->topjets->at(i).pt()>max_tag_pt)
        {
          tag_index=i;
          max_tag_pt=bcc->topjets->at(i).pt();
        }
      }
    }
    if (tag_index>-1)
    {
      int probe_index=-1;
      double max_probe_pt=-1;
      for (unsigned int i=0; i<bcc->topjets->size(); i++)
      {
        if (bcc->topjets->at(i).pt()>max_probe_pt && i!=tag_index)
        {
          probe_index=i;
          max_probe_pt=bcc->topjets->at(i).pt();
        }
      }
      if (probe_index>-1)
      {
        //Indices={antitag_index,probe_index};
        // std::vector<float> csv;
        // csv=bcc->topjets->at(probe_index).btagsub_combinedSecondaryVertex();
        // float maxcsv = *max_element(std::begin(csv), std::end(csv));
        // 	float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
        Hist("mass_shape")->Fill(TopJetMass(bcc->topjets->at(probe_index)),weight);
        // 	Hist("mass_shapeJEC")->Fill(bcc->topjets->at(probe_index).v4().M(),weight);
        // 	((TH2F*)Hist("mass_shape2D"))->Fill(TopJetMass(bcc->topjets->at(probe_index)),maxcsv,weight);
      }
    }
  }
  
  //mistag computation OLD
  //   if (doMistag)
  //   {
  //     int antitag_index=-1;
  //     double max_antitag_pt=-1;
  //     for (unsigned int i=0; i<bcc->topjets->size(); i++)
  //     {
  //       if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(i)) ) && ( MassAndPtCut(bcc->topjets->at(i)) ) )
  //       {
  // 	if (bcc->topjets->at(i).pt()>max_antitag_pt)
  // 	{
  // 	  antitag_index=i;
  // 	  max_antitag_pt=bcc->topjets->at(i).pt();
  // 	}
  //       }
  //     }
  //     if (antitag_index>-1)
  //     {
  //       int probe_index=-1;
  //       double max_probe_pt=-1;
  //       for (unsigned int i=0; i<bcc->topjets->size(); i++)
  //       {
  // 	if (bcc->topjets->at(i).pt()>max_probe_pt && i!=antitag_index)
  // 	{
  // 	  probe_index=i;
  // 	  max_probe_pt=bcc->topjets->at(i).pt();
  // 	}
  //       }
  //       if (probe_index>-1)
  //       {
  // 	//Indices={antitag_index,probe_index};
  // 	// std::vector<float> csv;
  // 	// csv=bcc->topjets->at(probe_index).btagsub_combinedSecondaryVertex();
  // 	// float maxcsv = *max_element(std::begin(csv), std::end(csv));
  // 	float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
  // 	((TH2F*)Hist("den_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
  // 	//((ZprimeFullHadHists*)antitag_den)->Fill2(Indices);
  // 	if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
  // 	{
  // 	  ((TH2F*)Hist("num_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
  // 	  //((ZprimeFullHadHists*)antitag_num)->Fill2(Indices);
  // 	}
  //       }
  //     }
  //   }
  
  //mistag computation
  if (doMistag)
  {
    unsigned int antitag_index=0;
    unsigned int probe_index=0;
    bool isantitagged=false;
    
    //
    
    if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(0)) ) && ( MassAndPtCutWithMatch(bcc->topjets->at(0)) ) )
    {
      antitag_index=0;
      probe_index=1;
      isantitagged=true;
    }
    else
    {
      if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(1)) ) && ( MassAndPtCutWithMatch(bcc->topjets->at(1)) ) )
      {
        antitag_index=1;
        probe_index=0;
        isantitagged=true;
      }
    }
    if(isantitagged)
    {
      //       cout<<probe_index<<bcc->topjets->size()<<endl;
      //       cout<<bcc->topjets->at(probe_index).pt()<<endl;
      float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
      ((TH2F*)Hist("den_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
      if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
      {
        ((TH2F*)Hist("num_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
      }
    }
    
    //     int antitag_index=-1;
    //     double max_antitag_pt=-1;
    //     for (unsigned int i=0; i<bcc->topjets->size(); i++)
    //     {
    //       if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(i)) ) && ( MassAndPtCut(bcc->topjets->at(i)) ) )
    //       {
    // 	if (bcc->topjets->at(i).pt()>max_antitag_pt)
    // 	{
    // 	  antitag_index=i;
    // 	  max_antitag_pt=bcc->topjets->at(i).pt();
    // 	}
    //       }
    //     }
    //     if (antitag_index>-1)
    //     {
    //       int probe_index=-1;
    //       double max_probe_pt=-1;
    //       for (unsigned int i=0; i<bcc->topjets->size(); i++)
    //       {
    // 	if (bcc->topjets->at(i).pt()>max_probe_pt && i!=antitag_index)
    // 	{
    // 	  probe_index=i;
    // 	  max_probe_pt=bcc->topjets->at(i).pt();
    // 	}
    //       }
    //       if (probe_index>-1)
    //       {
    // 	//Indices={antitag_index,probe_index};
    // 	// std::vector<float> csv;
    // 	// csv=bcc->topjets->at(probe_index).btagsub_combinedSecondaryVertex();
    // 	// float maxcsv = *max_element(std::begin(csv), std::end(csv));
    // 	float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
    // 	((TH2F*)Hist("den_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
    // 	//((ZprimeFullHadHists*)antitag_den)->Fill2(Indices);
    // 	if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
    // 	{
    // 	  ((TH2F*)Hist("num_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
    // 	  //((ZprimeFullHadHists*)antitag_num)->Fill2(Indices);
    // 	}
    //       }
    //     }
  }
  
  if(doMeasured && !IsRealData)
  {
    if(HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1)))
    {
      int nbtags=0;
      if (subJetBTag(bcc->topjets->at(0),e_CSVM)>0) nbtags++;
      if (subJetBTag(bcc->topjets->at(1),e_CSVM)>0) nbtags++;
      double mtt=getMtt(bcc->topjets->at(0),bcc->topjets->at(1));
      double mttJEC=(bcc->topjets->at(0).v4()+bcc->topjets->at(1).v4()).M();
      Hist("MeasuredMtt012")->Fill(mtt,weight);
      Hist("MeasuredJECMtt012")->Fill(mttJEC,weight);
      
      TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(0).subjets().at(0).eta()*1000000)*100000)));
      unsigned int histo_index;
      if (rand.Uniform(1.)<=0.5) histo_index=0; else histo_index=1;
      Hist("MeasuredHT012")->Fill(getHT50(bcc),weight);
      Hist("MeasuredpT012")->Fill(bcc->topjets->at(histo_index).pt(),weight);
      Hist("MeasuredCSV012")->Fill(getMaxCSV(bcc->topjets->at(histo_index)),weight);
      if (nbtags==0)
      {
        Hist("MeasuredMtt0")->Fill(mtt,weight);
        Hist("MeasuredJECMtt0")->Fill(mttJEC,weight);
        Hist("MeasuredHT0")->Fill(getHT50(bcc),weight);
        Hist("MeasuredpT0")->Fill(bcc->topjets->at(histo_index).pt(),weight);
        Hist("MeasuredCSV0")->Fill(getMaxCSV(bcc->topjets->at(histo_index)),weight);
      }
      else
      {
        if (nbtags==1)
        {
          Hist("MeasuredMtt1")->Fill(mtt,weight);
          Hist("MeasuredJECMtt1")->Fill(mttJEC,weight);
          Hist("MeasuredHT1")->Fill(getHT50(bcc),weight);
          Hist("MeasuredpT1")->Fill(bcc->topjets->at(histo_index).pt(),weight);
          Hist("MeasuredCSV1")->Fill(getMaxCSV(bcc->topjets->at(histo_index)),weight);
        }
        else
        {
          if (nbtags==2)
          {
            Hist("MeasuredMtt2")->Fill(mtt,weight);
            Hist("MeasuredJECMtt2")->Fill(mttJEC,weight);
            Hist("MeasuredHT2")->Fill(getHT50(bcc),weight);
            Hist("MeasuredpT2")->Fill(bcc->topjets->at(histo_index).pt(),weight);
            Hist("MeasuredCSV2")->Fill(getMaxCSV(bcc->topjets->at(histo_index)),weight);
          }
        }
      }
    }
    
    if(HepTopTag(bcc->toptagjets->at(0))&&HepTopTag(bcc->toptagjets->at(1)))
    {
      int nbtags=0;
      if (subJetBTag(bcc->toptagjets->at(0),e_CSVM)>0) nbtags++;
      if (subJetBTag(bcc->toptagjets->at(1),e_CSVM)>0) nbtags++;
      double mtt=getMtt(bcc->toptagjets->at(0),bcc->toptagjets->at(1));
      double mttJEC=(bcc->toptagjets->at(0).v4()+bcc->toptagjets->at(1).v4()).M();
      Hist("MeasuredHTTMtt012")->Fill(mtt,weight);
      Hist("MeasuredHTTJECMtt012")->Fill(mttJEC,weight);
      TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(0).subjets().at(0).eta()*1000000)*100000)));
      unsigned int histo_index;
      if (rand.Uniform(1.)<=0.5) histo_index=0; else histo_index=1;
      Hist("MeasuredHTTHT012")->Fill(getHT50(bcc),weight);
      Hist("MeasuredHTTpT012")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
      Hist("MeasuredHTTCSV012")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
      if (nbtags==0)
      {
        Hist("MeasuredHTTMtt0")->Fill(mtt,weight);
        Hist("MeasuredHTTJECMtt0")->Fill(mttJEC,weight);
        Hist("MeasuredHTTHT0")->Fill(getHT50(bcc),weight);
        Hist("MeasuredHTTpT0")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
        Hist("MeasuredHTTCSV0")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
      }
      else
      {
        if (nbtags==1)
        {
          Hist("MeasuredHTTMtt1")->Fill(mtt,weight);
          Hist("MeasuredHTTJECMtt1")->Fill(mttJEC,weight);
          Hist("MeasuredHTTHT1")->Fill(getHT50(bcc),weight);
          Hist("MeasuredHTTpT1")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
          Hist("MeasuredHTTCSV1")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
        }
        else
        {
          if (nbtags==2)
          {
            Hist("MeasuredHTTMtt2")->Fill(mtt,weight);
            Hist("MeasuredHTTJECMtt2")->Fill(mttJEC,weight);
            Hist("MeasuredHTTHT2")->Fill(getHT50(bcc),weight);
            Hist("MeasuredHTTpT2")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
            Hist("MeasuredHTTCSV2")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
          }
        }
      }
      
      //AK5 code
      vector<unsigned int> ak5indices;
      LorentzVector ak5v4(0,0,0,0);
      int topjet0ak5count=0;
      int topjet1ak5count=0;
      int nak5btag=0;
      bool istopjet0ak5btag=false;
      bool istopjet1ak5btag=false;
      bool isgood=true;
      for(unsigned int iak5=0; iak5<bcc->jets->size(); iak5++)
      {
        if (topjet0ak5count<=3)
        {
          if (bcc->toptagjets->at(0).deltaR(bcc->jets->at(iak5))<1.5)
          {
            ak5v4=ak5v4+bcc->jets->at(iak5).v4();
            topjet0ak5count++;
            ak5indices.push_back(iak5);
          }
        }
        if (topjet1ak5count<=3)
        {
          if (bcc->toptagjets->at(1).deltaR(bcc->jets->at(iak5))<1.5)
          {
            ak5v4=ak5v4+bcc->jets->at(iak5).v4();
            topjet1ak5count++;
            ak5indices.push_back(iak5);
          }
        }
      }
      if (istopjet0ak5btag) nak5btag++;
      if (istopjet1ak5btag) nak5btag++;
      for(unsigned int ch1=0; ch1<ak5indices.size()-1; ch1++)
      {
        for(unsigned int ch2=ch1+1; ch2<ak5indices.size(); ch2++)
        {
          if (ak5indices[ch1]==ak5indices[ch2])
          {
            isgood=false;
            cout<<ak5indices[ch1]<<" not good\n";
          }
        }
      }
      if (isgood)
      {
        double mttAK5=ak5v4.M();
        Hist("MeasuredAK5Mtt012")->Fill(mttAK5,weight);
        if (nak5btag==0)
        {
          Hist("MeasuredAK5Mtt0")->Fill(mttAK5,weight);
        }
        else
        {
          if (nak5btag==1)
          {
            Hist("MeasuredAK5Mtt1")->Fill(mttAK5,weight);
          }
          else
          {
            if (nak5btag==2)
            {
              Hist("MeasuredAK5Mtt2")->Fill(mttAK5,weight);
            }
          }
        }
      }
    }
    
  }
  
}


void BackgroundHists::Finish()
{
  delete mistag;
  delete mistagmc;
  delete shape;
  f->Close();
  delete f;
  //   delete f_pari;
  //   delete f_dispari;
  
}

