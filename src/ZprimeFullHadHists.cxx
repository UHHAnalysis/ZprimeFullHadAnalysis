#include "include/ZprimeFullHadTools.h"
#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"
#include "TH2.h"
#include <iostream>

using namespace std;

ZprimeFullHadHists::ZprimeFullHadHists(const char* name) : BaseHists(name)
{
  // named default constructor
//   TopJetIndices.push_back(-1);
//   TopJetIndices.push_back(-1);
  TopJetIndices={-1,-1};
}

ZprimeFullHadHists::~ZprimeFullHadHists(){
}

void ZprimeFullHadHists::Init()
{
  // book all histograms here

  // missing ET and HT
//   double* logMET_bins = MakeLogBinning(40, 50, 1200);
//   Book( TH1F( "MET_lx", "missing E_{T} [GeV]", 40, logMET_bins ) );
//   delete[] logMET_bins;
  
  double* logHT_bins = MakeLogBinning(40, 150, 3000);
  Book( TH1F( "HT_lx", "H_{T} [GeV]", 40, logHT_bins ) );
  delete[] logHT_bins;
  
//   double* logHTlep_bins = MakeLogBinning(40, 150, 1200);
//   Book( TH1F( "HTlep_lx", "H_{T}^{lep} [GeV]", 40, logHTlep_bins ) );
//   delete[] logHTlep_bins;
// 
//   // jets
//   Book( TH1F( "N_jets_ly", "N^{jets}", 20, 0, 20 ) );
//   double* logPtjet1_bins = MakeLogBinning(40, 150, 1500);
//   double* logPtjet2_bins = MakeLogBinning(40, 50, 1000);
//   double* logPtjet3_bins = MakeLogBinning(40, 50, 500);
//   double* logPtjet4_bins = MakeLogBinning(40, 50, 250);
//   Book( TH1F( "pt_jet1_lx", "p_{T}^{jet 1} [GeV/c]", 40, logPtjet1_bins ) );
//   Book( TH1F( "pt_jet2_lx", "p_{T}^{jet 2} [GeV/c]", 40, logPtjet2_bins ) ); 
//   Book( TH1F( "pt_jet3_lx", "p_{T}^{jet 3} [GeV/c]", 40, logPtjet3_bins ) );
//   Book( TH1F( "pt_jet4_lx", "p_{T}^{jet 4} [GeV/c]", 40, logPtjet4_bins ) );
//   delete[] logPtjet1_bins;
//   delete[] logPtjet2_bins;
//   delete[] logPtjet3_bins;
//   delete[] logPtjet4_bins;
  
  
//   Book( TH1F( "eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5) );
//   Book( TH1F( "eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5) );
//   Book( TH1F( "eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5) );
//   Book( TH1F( "eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5) );

  // leptons
//   Book( TH1F( "N_mu", "N^{#mu}", 10, 0, 10 ) );
//   double* logPtlep_bins = MakeLogBinning(40, 45, 500);
//   Book( TH1F( "pt_mu_lx", "p_{T}^{#mu} [GeV/c]", 40, logPtlep_bins ) );
//   delete[] logPtlep_bins;
//   
//   Book( TH1F( "eta_mu", "#eta^{#mu}", 40, -2.1, 2.1) );
//   Book( TH1F( "reliso_mu", "#mu rel. Iso", 40, 0, 0.5) );


  // primary vertices
  Book( TH1F( "N_pv", "N^{PV}", 50, 0, 50 ) );
//   Book( TH1F( "N_events_perLumiBin", "N^{evt}", 24, 0, 24 ) );
//   Book( TH1F( "N_pv_perLumiBin", "N^{PV}", 24, 0, 24 ) );

  Book( TH1F( "Ntopjets", "Ntopjets", 10, 0, 10 ) );
  Book( TH1F( "Njets", "Njets", 20, 0, 20 ) );
  Book( TH2F( "Njetsvspt", "Njetsvspt", 20, 0, 20 ,50,0,1000) );
  Book( TH1F( "SumOfTopCandidatesPt", "Sum of Jet pT (Top Tag candidates) [GeV];Sum of Jet pT (Top Tag candidates) [GeV];Events", 15, 0, 1500 ) );
  Book( TH1F( "LeadingTopCandidatePt", "Leading Jet pT (Top Tag candidate) [GeV];Leading Jet pT (Top Tag candidate) [GeV];Events", 15, 0, 1500 ) );
  Book( TH1F( "SubLeadingTopCandidatePt", "Subleading Jet pT (Top Tag candidate) [GeV];Subleading Jet pT (Top Tag candidate) [GeV];Events", 15, 0, 1500 ) );
  Book( TH1F( "TopCandidate1Pt", "Jet 1 pT (Top Tag candidate) [GeV];Jet 1 pT (Top Tag candidate) [GeV];Events", 30, 0, 1500 ) );
  Book( TH1F( "TopCandidate2Pt", "Jet 2 pT (Top Tag candidate) [GeV];Jet 2 pT (Top Tag candidate) [GeV];Events", 30, 0, 1500 ) );
  Book( TH1F( "Mtt", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Nevts", "Nevts", 1, 0, 1 ) );
  double pt_bins[] = {200,400,600,10000};
  Book( TH1F("ptNevts","Top pT [GeV];Top pT [GeV];Events",sizeof(pt_bins)/sizeof(double)-1,pt_bins));
  double toppt_bins[] = {0,40,80,120,160,200,240,280,320,360,400,500,600,1000};
  Book( TH1F("toppt","Top pT [GeV];Top pT [GeV];Events",sizeof(toppt_bins)/sizeof(double)-1,toppt_bins));
  Book( TH1F( "DeltaY", "#Delta y;#Delta y;Events", 200, 0, 10 ) );
  Book( TH1F( "DeltaEta", "#Delta Eta;#Delta Eta;Events", 200, 0, 5 ) );
  Book( TH1F( "DeltaPhi", "#Delta Phi;#Delta Phi;Events", 200, 0, 4 ) );
  Book( TH1F( "DeltaR", "#Delta R;#Delta R;Events", 200, 0, 10 ) );
  Book( TH1F( "Nsub", "#tau_{3}/#tau_{2};#tau_{3}/#tau_{2};Events", 100, 0, 1 ) );
  Book( TH2F( "pT2D", "pT;pT;pT", 30, 0, 1500 ,30, 0, 1500 ) );
  Book( TH2F( "pT2D12", "pT;pT;pT", 30, 0, 1500 ,30, 0, 1500 ) );
  
//   TopJetIndices.clear();
//   TopJetIndices.push_back(-1);
//   TopJetIndices.push_back(-1);
  TopJetIndices={-1,-1};
}

void ZprimeFullHadHists::setIndices(std::vector<int> Indices)
{
  TopJetIndices = Indices;
}

void ZprimeFullHadHists::Fill2(std::vector<int> Indices, string version, bool useCMSTT)
{
  std::vector< TopJet >* collection = NULL;

  
    // fill the histograms
  TopJetIndices = Indices;

  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
//   LuminosityHandler* lumih = calc->GetLumiHandler();

  // important: get the event weight
  double weight = calc->GetWeight();
  //weight=1.0;////////////////////////////////////////////////
  
//   int run = calc->GetRunNum();
//   int lumiblock = calc->GetLumiBlock();
  int Npvs = calc->GetPrimaryVertices()->size();

  Hist("N_pv")->Fill(Npvs, weight);
//   if(calc->IsRealData()){  
//     Hist( "N_pv_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), Npvs*weight);
//     Hist( "N_events_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), weight);
//   }

  //double npu = bcc.genInfo->pileup_TrueNumInteractions();
  //if(npu>50) npu=49.9999;
  //Hist( "N_pileup_hist" )->Fill( npu, weight );

//   MET* met = calc->GetMET();
//   Hist("MET_lx")->Fill(met->pt(), weight);

  double HT = calc->GetHT();
  Hist("HT_lx")->Fill(HT, weight);

//   double HTlep = calc->GetHTlep();
//   Hist("HTlep_lx")->Fill(HTlep, weight);
// 
//   std::vector<Jet>* jets = calc->GetJets();
//   int Njets = jets->size();
//   Hist("N_jets_ly")->Fill(Njets, weight);

//   if(Njets>=1){
//     Hist("pt_jet1_lx")->Fill(jets->at(0).pt(), weight);
//     Hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
//   }
//   if(Njets>=2){
//     Hist("pt_jet2_lx")->Fill(jets->at(1).pt(), weight);
//     Hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
//   }
//   if(Njets>=3){
//     Hist("pt_jet3_lx")->Fill(jets->at(2).pt(), weight);
//     Hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
//   }
//   if(Njets>=4){
//     Hist("pt_jet4_lx")->Fill(jets->at(3).pt(), weight);
//     Hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
//   }

//   std::vector<Muon>* muons = calc->GetMuons();
//   int Nmuons = muons->size();
//   Hist("N_mu")->Fill(Nmuons, weight);
//   for (int i=0; i<Nmuons; ++i){
//     Muon thismu = muons->at(i);
//     Hist("pt_mu_lx")->Fill(thismu.pt(), weight);
//     Hist("eta_mu")->Fill(thismu.eta(), weight);
// 
//     Hist("reliso_mu")->Fill(thismu.relIso(), weight);
//   }

  //std::vector<int> TopJetIndices = getTopJetsIndices(bcc,1,1,1,1,0,0,200.);
  if (useCMSTT) collection=bcc->higgstagjets; else collection=bcc->toptagjets;
  
  Hist("Nevts")->Fill(0.5,weight);
  Hist("Ntopjets")->Fill(collection->size(),weight);
  int nj=0;
  for (unsigned int ii=0; ii<bcc->jets->size(); ii++)
  {
    if (bcc->jets->at(ii).pt()>50.0) nj++;
  }
  Hist("Njets")->Fill(nj,weight);
  if(TopJetIndices[0]>=0)
  {
    Hist("ptNevts")->Fill(collection->at(TopJetIndices[0]).pt(),weight);
    Hist("toppt")->Fill(collection->at(TopJetIndices[0]).pt(),weight);
  }
  if (checkIndices(TopJetIndices))
  {
    HEPTopTaggerReweight httr;
    double htt_weight=1.0;
//     if (version=="TTbarLept" || version=="TTbarSemi" || version=="TTbarHad") htt_weight=httr.GetScaleWeight(TopJetIndices);
    ((TH2F*)Hist("Njetsvspt"))->Fill(nj,collection->at(TopJetIndices[0]).pt(),weight*htt_weight);
    Hist("SumOfTopCandidatesPt")->Fill(collection->at(TopJetIndices[0]).pt()+collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
    if ( collection->at(TopJetIndices[0]).pt() > collection->at(TopJetIndices[1]).pt() )
    {
      Hist("LeadingTopCandidatePt")->Fill(collection->at(TopJetIndices[0]).pt(),weight*htt_weight);
      Hist("SubLeadingTopCandidatePt")->Fill(collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
      ((TH2F*)Hist( "pT2D" ))->Fill(collection->at(TopJetIndices[0]).pt(),collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
    }
    else
    {
      Hist("LeadingTopCandidatePt")->Fill(collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
      Hist("SubLeadingTopCandidatePt")->Fill(collection->at(TopJetIndices[0]).pt(),weight*htt_weight);
      ((TH2F*)Hist( "pT2D" ))->Fill(collection->at(TopJetIndices[1]).pt(),collection->at(TopJetIndices[0]).pt(),weight*htt_weight);
    }
    Hist("TopCandidate1Pt")->Fill(collection->at(TopJetIndices[0]).pt(),weight*htt_weight);
    Hist("TopCandidate2Pt")->Fill(collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
    Hist("Mtt")->Fill((collection->at(TopJetIndices[0]).v4()+collection->at(TopJetIndices[1]).v4()).M(),weight*htt_weight);
    Hist( "DeltaY" )->Fill(deltaY(bcc,TopJetIndices),weight*htt_weight);
    Hist(  "Nsub"  )->Fill(getNsub(bcc,TopJetIndices[0]),weight*htt_weight);
    Hist( "DeltaEta" )->Fill(fabs(collection->at(TopJetIndices[0]).eta()-collection->at(TopJetIndices[1]).eta()),weight*htt_weight);
    Hist( "DeltaPhi" )->Fill(collection->at(TopJetIndices[0]).deltaPhi(collection->at(TopJetIndices[1])),weight*htt_weight);
    Hist( "DeltaR" )->Fill(collection->at(TopJetIndices[0]).deltaR(collection->at(TopJetIndices[1])),weight*htt_weight);
    ((TH2F*)Hist( "pT2D12" ))->Fill(collection->at(TopJetIndices[0]).pt(),collection->at(TopJetIndices[1]).pt(),weight*htt_weight);
  }
  
//   TopJetIndices = Indices;
//   Fill();
}

void ZprimeFullHadHists::Fill()
{
  std::vector<int> Indices = {-1,-1};
  Fill2(Indices);
}

void ZprimeFullHadHists::Finish()
{
  // final calculations, like division and addition of certain histograms
//   EventCalc* calc = EventCalc::Instance();
//   bool IsRealData = calc->IsRealData();
//   if (IsRealData){
//     Hist("N_pv_perLumiBin")->Divide( Hist("N_pv_perLumiBin"), Hist("N_events_perLumiBin"));
//     Hist( "N_pv_perLumiBin")->GetYaxis()->SetTitle("Events/Lumi");
//   }

}

