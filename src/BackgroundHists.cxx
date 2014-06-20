#include "include/ZprimeFullHadTools.h"
#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TRandom3.h"

using namespace std;

BackgroundHists::BackgroundHists(const char* name) : BaseHists(name)
{
  f = new TFile("/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/bkg.root");
  mistag = (TH2F*)f->Get("HTDatasetHistos/Mistag/data_htt/Mistag_data_htt");
  mjmistag = (TH2F*)f->Get("QuadJetDatasetHistos/Mistag/data_htt/Mistag_data_htt");
//   mistagmc = (TH3F*)f->Get("HEPTagger/Mistag/qcd500to1000/Mistag_qcd500to1000");/////////////////////////////////////////////////////////////
  mistagmc = (TH2F*)f->Get("HTDatasetHistos/Mistag/qcd_htt/Mistag_qcd_htt");
  mjmistagmc = (TH2F*)f->Get("QuadJetDatasetHistos/Mistag/qcd_htt/Mistag_qcd_htt");
//   mjmistagmc = (TH2F*)f->Get("QuadJetDatasetHistos/Mistag/qcd500to1000/Mistag_qcd500to1000");
//   shape = (TH1F*)f->Get("HTDatasetHistos/MassShape/qcd_htt/mass_shape_qcd_htt");
// mjshape = (TH1F*)f->Get("QuadJetDatasetHistos/MassShape/qcd_htt/mass_shape_qcd_htt");//should be MC!!!!!!!!!!
  
shapehigh = (TH1F*)f->Get("HTDatasetHistos/MassShape/qcd_htt/mass_shape_high");
shapelow = (TH1F*)f->Get("HTDatasetHistos/MassShape/qcd_htt/mass_shape_low");
mjshapehigh = (TH1F*)f->Get("QuadJetDatasetHistos/MassShape/qcd_htt/mass_shape_high");
mjshapelow = (TH1F*)f->Get("QuadJetDatasetHistos/MassShape/qcd_htt/mass_shape_low");

mjshape = (TH1F*)f->Get("QuadJetDatasetHistos/MassShape/qcd_htt/mass_shape");
shape = (TH1F*)f->Get("HTDatasetHistos/MassShape/qcd_htt/mass_shape");

  
  //   mjshape = (TH1F*)f->Get("QuadJetDatasetHistos/MassShape/qcd500to1000/mass_shape_qcd500to1000");
//   shape = (TH1F*)f->Get("HEPTagger/MassShape/qcd500to1000/mass_shape_qcd500to1000");/////////////////////////
}

BackgroundHists::~BackgroundHists(){
}

void BackgroundHists::setVersion(string s)
{
  version=s;
}

void BackgroundHists::setEventNumber(unsigned int evt)
{
  event_number=evt;
}

void BackgroundHists::setRegion(string r)
{
  region=r;
}

void BackgroundHists::Init()
{
  
  double csv_bins[] = {-100.0,0.0,0.244,0.679,10.0};
  double mistag_pt_bins[] = {150.0,200.0,220.0,240.0,260.0,280.0,300.0,320.0,340.0,360.0,380.0,400.0,450.0,500.0,600.0,800.0,2000.0};
  
  double ht_shape_bins[] = {0,500,600,700,1200};
  double pt_shape_bins[] = {150,175,200,220,250,1000};
  double mass_shape_bins[]= {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 256, 264, 272, 280, 288, 296, 304, 312, 320, 328, 336, 344, 352, 360, 368, 376, 384, 392, 400};
  
  Book( TH1F( "Mtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "Mtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
//   Book( TH1F( "MttNoMass0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MttNoMass1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MttNoMass2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MttNoMass012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
  Book( TH1F( "MeasuredMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  Book( TH1F( "MeasuredMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
 
  Book( TH1F( "MeasuredJet1pT0", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet1pT1", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet1pT2", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet1pT012", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  
  Book( TH1F( "MeasuredJet2pT0", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet2pT1", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet2pT2", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "MeasuredJet2pT012", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  
  Book( TH1F( "MeasuredJet1eta0", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet1eta1", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet1eta2", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet1eta012", ";#eta;Events", 50, -2.5, 2.5 ) );
  
  Book( TH1F( "MeasuredJet2eta0", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet2eta1", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet2eta2", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "MeasuredJet2eta012", ";#eta;Events", 50, -2.5, 2.5 ) );
  
  Book( TH1F( "MeasuredJet1csv0", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet1csv1", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet1csv2", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet1csv012", ";#beta_{max};Events", 50, 0, 1.01 ) );
  
  Book( TH1F( "MeasuredJet2csv0", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet2csv1", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet2csv2", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "MeasuredJet2csv012", ";#beta_{max};Events", 50, 0, 1.01 ) );
  
  
  
  Book( TH1F( "Jet1pT0", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet1pT1", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet1pT2", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet1pT012", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  
  Book( TH1F( "Jet2pT0", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet2pT1", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet2pT2", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  Book( TH1F( "Jet2pT012", ";p_{T} [GeV];Events", 50, 0, 1500 ) );
  
  Book( TH1F( "Jet1eta0", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet1eta1", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet1eta2", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet1eta012", ";#eta;Events", 50, -2.5, 2.5 ) );
  
  Book( TH1F( "Jet2eta0", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet2eta1", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet2eta2", ";#eta;Events", 50, -2.5, 2.5 ) );
  Book( TH1F( "Jet2eta012", ";#eta;Events", 50, -2.5, 2.5 ) );
  
  Book( TH1F( "Jet1csv0", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet1csv1", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet1csv2", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet1csv012", ";#beta_{max};Events", 50, 0, 1.01 ) );
  
  Book( TH1F( "Jet2csv0", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet2csv1", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet2csv2", ";#beta_{max};Events", 50, 0, 1.01 ) );
  Book( TH1F( "Jet2csv012", ";#beta_{max};Events", 50, 0, 1.01 ) );
  
  Book( TH1F( "m1",";m;Events",200,0.0,400.0));
  Book( TH1F( "m2",";m;Events",200,0.0,400.0));
  Book( TH1F( "mchanged",";m;Events",200,0.0,400.0));
  Book( TH1F( "Njets", "Njets", 20, 0, 20 ) );
  Book( TH1F( "Njets50", "Njets", 20, 0, 20 ) );
  Book( TH1F( "pT4", "pT4", 100, 0, 500 ) );
  Book( TH1F( "spT4", ";spT4;Events", 100, 0, 1000 ) );
  Book( TH1F( "sToppT", ";sToppT;Events", 100, 0, 1000 ) );
  Book( TH1F( "HT50", "HT", 100, 0, 2000 ) );
  Book( TH2F( "HTT2D1", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));
  Book( TH2F( "HTT2D2", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));
  
  Book( TH1F( "pT5", "pT5", 100, 0, 500 ) );
  Book( TH1F( "spT5", ";spT5;Events", 100, 0, 1000 ) );
  Book( TH2F( "Whichmistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins) );
  Book( TH2F( "HTT2Dtag", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));
  Book( TH2F( "HTT2Dmistag", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));
  Book( TH1F( "MeasuredpT5", "pT5", 100, 0, 500 ) );
  Book( TH1F( "MeasuredspT5", ";spT5;Events", 100, 0, 1000 ) );
  
  Book( TH1F( "Measuredm1",";m;Events",200,0.0,400.0));
  Book( TH1F( "Measuredm2",";m;Events",200,0.0,400.0));
  Book( TH1F( "MeasuredNjets", "Njets", 20, 0, 20 ) );
  Book( TH1F( "MeasuredNjets50", "Njets", 20, 0, 20 ) );
  Book( TH1F( "MeasuredpT4", "pT4", 100, 0, 500 ) );
  Book( TH1F( "MeasuredspT4", ";spT4;Events", 100, 0, 1000 ) );
  Book( TH1F( "MeasuredsToppT", ";sToppT;Events", 100, 0, 1000 ) );
  Book( TH1F( "MeasuredHT50", "HT", 100, 0, 2000 ) );
  Book( TH2F( "MeasuredHTT2D1", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));
  Book( TH2F( "MeasuredHTT2D2", ";atan(m_{13}/m_{12});m_{23}/m_{123}",200 ,0. ,3., 200,0. ,2.));

  
//   Book( TH1F( "MeasuredJECMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredJECMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredJECMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredJECMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   
//   Book( TH1F( "MeasuredHTTMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   
//   Book( TH1F( "MeasuredHTTJECMtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTJECMtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTJECMtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredHTTJECMtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   
//   Book( TH1F( "MeasuredAK5Mtt0", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredAK5Mtt1", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredAK5Mtt2", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "MeasuredAK5Mtt012", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
  
//   Book( TH1F( "Mtt012NoWeight", "Mtt [GeV];Mtt [GeV];Events", 80, 0, 4000 ) );
//   Book( TH1F( "CSV012NoWeight", ";CSV;Events", 260, -11, 2 ) );
//   Book( TH1F( "HT012NoWeight", ";HT;Events", 300, 0, 6000 ) );
//   Book( TH1F( "pT012NoWeight", ";pT;Events", 100, 0, 2000 ) );
  
//   Book( TH1F( "CSV012", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredCSV012", ";CSV;Events", 260, -11, 2 ) );
//   Book( TH1F( "HTTCSV012", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredHTTCSV012", ";CSV;Events", 260, -11, 2 ) );
//   
//   Book( TH1F( "HT012", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHT012", ";HT;Events", 300, 0, 6000 ) );
//   Book( TH1F( "HTTHT012", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHTTHT012", ";HT;Events", 300, 0, 6000 ) );
//   
//   Book( TH1F( "pT012", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredpT012", ";pT;Events", 100, 0, 2000 ) );
//   Book( TH1F( "HTTpT012", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredHTTpT012", ";pT;Events", 100, 0, 2000 ) );
//   
//   
//   
//   Book( TH1F( "CSV0", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredCSV0", ";CSV;Events", 260, -11, 2 ) );
//   Book( TH1F( "HTTCSV0", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredHTTCSV0", ";CSV;Events", 260, -11, 2 ) );
//   
//   Book( TH1F( "HT0", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHT0", ";HT;Events", 300, 0, 6000 ) );
//   Book( TH1F( "HTTHT0", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHTTHT0", ";HT;Events", 300, 0, 6000 ) );
//   
//   Book( TH1F( "pT0", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredpT0", ";pT;Events", 100, 0, 2000 ) );
//   Book( TH1F( "HTTpT0", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredHTTpT0", ";pT;Events", 100, 0, 2000 ) );
//   
//   
//   
//   Book( TH1F( "CSV1", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredCSV1", ";CSV;Events", 260, -11, 2 ) );
//   Book( TH1F( "HTTCSV1", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredHTTCSV1", ";CSV;Events", 260, -11, 2 ) );
//   
//   Book( TH1F( "HT1", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHT1", ";HT;Events", 300, 0, 6000 ) );
//   Book( TH1F( "HTTHT1", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHTTHT1", ";HT;Events", 300, 0, 6000 ) );
//   
//   Book( TH1F( "pT1", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredpT1", ";pT;Events", 100, 0, 2000 ) );
//   Book( TH1F( "HTTpT1", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredHTTpT1", ";pT;Events", 100, 0, 2000 ) );
//   
//   
//   
//   Book( TH1F( "CSV2", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredCSV2", ";CSV;Events", 260, -11, 2 ) );
//   Book( trueTH1F( "HTTCSV2", ";CSV;Events", 260, -11, 2 ) );
// //   Book( TH1F( "MeasuredHTTCSV2", ";CSV;Events", 260, -11, 2 ) );
//   
//   Book( TH1F( "HT2", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHT2", ";HT;Events", 300, 0, 6000 ) );
//   Book( TH1F( "HTTHT2", ";HT;Events", 300, 0, 6000 ) );
// //   Book( TH1F( "MeasuredHTTHT2", ";HT;Events", 300, 0, 6000 ) );
//   
//   Book( TH1F( "pT2", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredpT2", ";pT;Events", 100, 0, 2000 ) );
//   Book( TH1F( "HTTpT2", ";pT;Events", 100, 0, 2000 ) );
// //   Book( TH1F( "MeasuredHTTpT2", ";pT;Events", 100, 0, 2000 ) );
  
  //   Book( TH1F( "fake_mass",";m;Events",110,140.0,250.0));
//   double csv_bins[] = {-100.0,0.0,0.244,0.679,10.0};
// //   double csv_bins[] = {-100.0,0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,10.0};
//   double mistag_pt_bins[] = {150.0,200.0,220.0,240.0,260.0,280.0,300.0,320.0,340.0,360.0,380.0,400.0,450.0,500.0,600.0,800.0,2000.0};
  //{150.0,175.0,200.0,210.0,220.0,230.0,240.0,250.0,260.0,270.0,280.0,290.0,300.0,310.0,320.0,330.0,340.0,350.0,360.0,370.0,380.0,390.0,400.0,410.0,430.0,450.0,500.0,600.0,800.0,1000.0,2000.0};
  //double mistag_ht_bins[] = {0/*,300,400,450,500,550,600,650,700,800,1000*/,10000};
  //Book( TH3F( "num_mistag", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  //Book( TH3F( "den_mistag", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  
  Book( TH2F( "num_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins) );
  Book( TH2F( "den_mistag", ";pT;CSV", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins) );
  
  double mtt_bins[]={0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500, 1550, 1600, 1650, 1700, 1750, 1800,1850, 1900, 1950, 2000, 2050, 2100, 2150, 2200, 2250, 2300, 2350, 2400, 2450, 2500, 2550, 2600, 2650, 2700, 2750, 2800, 2850, 2900, 2950, 3000, 3050, 3100, 3150, 3200, 3250, 3300, 3350, 3400, 3450,3500, 3550, 3600, 3650, 3700, 3750, 3800, 3850, 3900, 3950,4000};
  
  Book( TH3F( "ErrMtt0", ";Mtt;pT;CSV", sizeof(mtt_bins)/sizeof(double)-1 , mtt_bins, sizeof(mistag_pt_bins)/sizeof(double)-1 , mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1 , csv_bins ) );
  Book( TH3F( "ErrMtt1", ";Mtt;pT;CSV", sizeof(mtt_bins)/sizeof(double)-1 , mtt_bins, sizeof(mistag_pt_bins)/sizeof(double)-1 , mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1 , csv_bins ) );
  Book( TH3F( "ErrMtt2", ";Mtt;pT;CSV", sizeof(mtt_bins)/sizeof(double)-1 , mtt_bins, sizeof(mistag_pt_bins)/sizeof(double)-1 , mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1 , csv_bins ) );
  
//   Book( TProfile3D( "mistag_crosscheck", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  //   Book( TH2F( "mass_shape2D",";m;CSV",110,140.0,250.0,sizeof(csv_bins)/sizeof(double)-1, csv_bins));
  //Book( TH1F( "mass_shape",";m;Events",200,0.0,400.0));
  Book( TH1F( "mass_shape",";m;Events",200,0.0,400.0));
  Book( TH1F( "mass_shape_low",";m;Events",200,0.0,400.0));
  Book( TH1F( "mass_shape_high",";m;Events",200,0.0,400.0));
  //Book( TH1F( "mass_shape_lowpt",";m;Events",200,0.0,400.0));
  //Book( TH1F( "mass_shape_highpt",";m;Events",200,0.0,400.0));
  
  //Book( TH2F( "mass_shape_ht",";ht;m;Events",sizeof(ht_shape_bins)/sizeof(double)-1,ht_shape_bins,sizeof(mass_shape_bins)/sizeof(double)-1,mass_shape_bins));
  //Book( TH2F( "mass_shape_pt",";pt;m;Events",sizeof(pt_shape_bins)/sizeof(double)-1,pt_shape_bins,sizeof(mass_shape_bins)/sizeof(double)-1,mass_shape_bins));
  //   Book( TH1F( "mass_shapeJEC",";m;Events",110,140.0,250.0));
  
//   Book( TH3F( "num_mistagMeasured", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
//   Book( TH3F( "den_mistagMeasured", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
// 
//   Book( TH3F( "num_mistagTag", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
//   Book( TH3F( "den_mistagTag", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  
/*  
  Book( TH3F( "num_mistagR", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  Book( TH3F( "den_mistagR", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  
  Book( TH3F( "num_mistagRmw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  Book( TH3F( "den_mistagRmw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  
  Book( TH3F( "num_mistagInvmw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  Book( TH3F( "den_mistagInvmw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  
  Book( TH3F( "num_mistagNomw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );
  Book( TH3F( "den_mistagNomw", ";pT;CSV;HT", sizeof(mistag_pt_bins)/sizeof(double)-1,mistag_pt_bins, sizeof(csv_bins)/sizeof(double)-1, csv_bins, sizeof(mistag_ht_bins)/sizeof(double)-1, mistag_ht_bins ) );*/
  
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
  
//   bool doMistag=false;
//   bool doMassShape=false;
//   bool doBackground=false;
//   bool doMeasured=true;
  
  bool isQCD = (version.find("QCD")!=string::npos);
  bool isEven = (event_number%2==0);
  float mttcut= -1;
  
  //mistag application
  if (doBackground && !(isQCD && isEven) )
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
      //double ht50=getHT50(bcc);
      //        cout<<bcc->topjets->at(mistag_index).pt()<<" "<<maxcsv<<endl;
      Int_t mistag_bin = 0;
      double mistag_value = 0;
      if (IsRealData||version=="TTbarHad"||version=="TTbarLept"||version=="TTbarSemi"||version=="TTbar")
      {
	if (region=="HTDatasetHistos")
	{
	  mistag_bin = mistag->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
	  mistag_value = mistag->GetBinContent(mistag_bin);
	}
	else
	{
	  mistag_bin = mjmistag->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
	  mistag_value= mjmistag->GetBinContent(mistag_bin);
	}
      }
      else
      {
	if (region=="HTDatasetHistos")
	{
	  mistag_bin = mistagmc->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
	  mistag_value=mistagmc->GetBinContent(mistag_bin);
	}
	else
	{
	  mistag_bin = mjmistagmc->FindFixBin(bcc->topjets->at(mistag_index).pt(),maxcsv);
	  mistag_value=mjmistagmc->GetBinContent(mistag_bin);
	}
//         Int_t binx=0;
//         Int_t biny=0;
//         Int_t binz=0;
//         mistagmc->GetBinXYZ(mistag_bin, binx, biny, binz);
//         Int_t aa=((TProfile3D*)Hist("mistag_crosscheck"))->Fill(bcc->topjets->at(mistag_index).pt(),maxcsv,ht50,mistag_value);
        //cout<<maxcsv<<" "<<mistag_bin<<" "<<binx<<" "<<biny<<" "<<binz<<" "<<bcc->topjets->at(mistag_index).pt()<<" "<<aa<<"\n";
        
        
      }
      //        cout<<mistag_bin<<endl;
      TLorentzVector TagVector;
      TLorentzVector MistagVector;
      //        cout<<gRandom->ClassName()<<endl;
      
      double etaseed2 = bcc->topjets->at(1).subjets().at(0).eta();
      int seed2 = abs(static_cast<int>(sin(etaseed2*1000000)*100000));
      gRandom->SetSeed(seed2);
      double RandomMass=0;
      if (region=="HTDatasetHistos")
      {
	RandomMass = shape->GetRandom();
      }
      else//QuadJetDatasetHistos
      {
// 	if (getMtt(bcc->topjets->at(tag_index),bcc->topjets->at(mistag_index))<500)
       if (bcc->topjets->at(mistag_index).pt()<220)
	  RandomMass = mjshapelow->GetRandom();
	else
	  RandomMass = mjshapehigh->GetRandom();
// 	  RandomMass = mjshape->GetRandom();
      }
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
//       double mtt=getMtt(bcc->topjets->at(0),bcc->topjets->at(1));//NO random mass modification
//       double mttNoMass=getMtt(bcc->topjets->at(0),bcc->topjets->at(1));//NO random mass modification
      unsigned int ileading = 0;
      unsigned int isubleading = 1;
      if (bcc->topjets->at(1).pt()>bcc->topjets->at(0).pt())
      {
	ileading = 1;
	isubleading = 0;
      }
      float leadingcsv=getMaxCSV(bcc->topjets->at(ileading));
      float subleadingcsv=getMaxCSV(bcc->topjets->at(isubleading));
      
      int nbtags=0;
      if (version=="TTbar")
      {
        if (subJetBTag(bcc->topjets->at(tag_index),e_CSVM,"mean","/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
        if (subJetBTag(bcc->topjets->at(mistag_index),e_CSVM,"mean","/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
        HEPTopTaggerReweight htt;
        mistag_value=mistag_value*htt.GetScaleWeight1(IndexWithMatch(bcc->topjets->at(tag_index)));
        //cout<<IndexWithMatch(bcc->topjets->at(tag_index))<<" "<<htt.GetScaleWeight1(IndexWithMatch(bcc->topjets->at(tag_index)))<<endl;
      }
      else
      {
        if (subJetBTag(bcc->topjets->at(tag_index),e_CSVM)>0) nbtags++;
        if (subJetBTag(bcc->topjets->at(mistag_index),e_CSVM)>0) nbtags++;
      }
      
        if (mtt>mttcut)
      {
      Hist("Mtt012")->Fill(mtt,mistag_value*weight);
      Hist("Jet1pT012")->Fill(bcc->topjets->at(ileading).pt(),weight*mistag_value);
      Hist("Jet2pT012")->Fill(bcc->topjets->at(isubleading).pt(),weight*mistag_value);
      Hist("Jet1eta012")->Fill(bcc->topjets->at(ileading).eta(),weight*mistag_value);
      Hist("Jet2eta012")->Fill(bcc->topjets->at(isubleading).eta(),weight*mistag_value);
      Hist("Jet1csv012")->Fill(leadingcsv,weight*mistag_value);
      Hist("Jet2csv012")->Fill(subleadingcsv,weight*mistag_value);
      
//       Hist("MttNoMass012")->Fill(mttNoMass,mistag_value*weight);
//       Hist("HT012")->Fill(ht50,mistag_value*weight);
//       Hist("pT012")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
//       Hist("CSV012")->Fill(maxcsv,mistag_value*weight);
      
//       Hist("Mtt012NoWeight")->Fill(mtt,weight);
//       //Hist("MttNoMass012NoWeight")->Fill(mttNoMass,weight);
//       Hist("HT012NoWeight")->Fill(ht50,weight);
//       Hist("pT012NoWeight")->Fill(bcc->topjets->at(mistag_index).pt(),weight);
//       Hist("CSV012NoWeight")->Fill(maxcsv,weight);
      if (nbtags==0)
      {
        Hist("Mtt0")->Fill(mtt,mistag_value*weight);
        ((TH3F*)Hist("ErrMtt0"))->Fill(mtt,bcc->topjets->at(mistag_index).pt(),maxcsv,weight);
	Hist("Jet1pT0")->Fill(bcc->topjets->at(ileading).pt(),weight*mistag_value);
	Hist("Jet2pT0")->Fill(bcc->topjets->at(isubleading).pt(),weight*mistag_value);
	Hist("Jet1eta0")->Fill(bcc->topjets->at(ileading).eta(),weight*mistag_value);
	Hist("Jet2eta0")->Fill(bcc->topjets->at(isubleading).eta(),weight*mistag_value);
	Hist("Jet1csv0")->Fill(leadingcsv,weight*mistag_value);
	Hist("Jet2csv0")->Fill(subleadingcsv,weight*mistag_value);
	
	Hist("mchanged")->Fill(TopJetMass(bcc->topjets->at(mistag_index)),weight*mistag_value);
	if (tag_index==ileading)
	{
	  Hist("m1")->Fill(TopJetMass(bcc->topjets->at(ileading)),weight*mistag_value);
	  Hist("m2")->Fill(RandomMass,weight*mistag_value);
	}
	else
	{
	  Hist("m1")->Fill(RandomMass,weight*mistag_value);
	  Hist("m2")->Fill(TopJetMass(bcc->topjets->at(isubleading)),weight*mistag_value);
	}
	Hist("Njets")->Fill(bcc->jets->size(),weight*mistag_value);
	int nj=0;
	for (unsigned int ii=0; ii<bcc->jets->size(); ii++)
	{
	  if (bcc->jets->at(ii).pt()>50.0) nj++;
	}
	Hist("Njets50")->Fill(nj,weight*mistag_value);
	Hist("sToppT")->Fill(bcc->topjets->at(0).pt()+bcc->topjets->at(1).pt(),weight*mistag_value);
	if (bcc->jets->size()>3)
	{
	  Hist("pT4")->Fill(bcc->jets->at(3).pt(),weight*mistag_value);
	  Hist("spT4")->Fill(bcc->jets->at(3).pt()+bcc->jets->at(2).pt()+bcc->jets->at(1).pt()+bcc->jets->at(0).pt(),weight*mistag_value);
	}
	Hist("HT50")->Fill(getHT50(bcc),weight*mistag_value);
	((TH2F*)Hist("HTT2D1"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(ileading)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(ileading)),weight*mistag_value);
	((TH2F*)Hist("HTT2D2"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(isubleading)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(isubleading)),weight*mistag_value);
	
	if (bcc->jets->size()>4)
	{
	  Hist("pT5")->Fill(bcc->jets->at(4).pt(),weight*mistag_value);
	  Hist("spT5")->Fill(bcc->jets->at(4).pt()+bcc->jets->at(3).pt()+bcc->jets->at(2).pt()+bcc->jets->at(1).pt()+bcc->jets->at(0).pt(),weight*mistag_value);
	}
	((TH2F*)Hist("Whichmistag"))->Fill(bcc->topjets->at(mistag_index).pt(),maxcsv,weight*mistag_value);
	((TH2F*)Hist("HTT2Dtag"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(tag_index)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(tag_index)),weight*mistag_value);
	((TH2F*)Hist("HTT2Dmistag"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(mistag_index)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(mistag_index)),weight*mistag_value);
	
	
//         Hist("MttNoMass0")->Fill(mttNoMass,mistag_value*weight);
//         Hist("HT0")->Fill(ht50,mistag_value*weight);
//         Hist("pT0")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
//         Hist("CSV0")->Fill(maxcsv,mistag_value*weight);
      }
      else
      {
        if (nbtags==1)
        {
          Hist("Mtt1")->Fill(mtt,mistag_value*weight);
          ((TH3F*)Hist("ErrMtt1"))->Fill(mtt,bcc->topjets->at(mistag_index).pt(),maxcsv,weight);
	  Hist("Jet1pT1")->Fill(bcc->topjets->at(ileading).pt(),weight*mistag_value);
	  Hist("Jet2pT1")->Fill(bcc->topjets->at(isubleading).pt(),weight*mistag_value);
	  Hist("Jet1eta1")->Fill(bcc->topjets->at(ileading).eta(),weight*mistag_value);
	  Hist("Jet2eta1")->Fill(bcc->topjets->at(isubleading).eta(),weight*mistag_value);
	  Hist("Jet1csv1")->Fill(leadingcsv,weight*mistag_value);
	  Hist("Jet2csv1")->Fill(subleadingcsv,weight*mistag_value);
//           Hist("MttNoMass1")->Fill(mttNoMass,mistag_value*weight);
//           Hist("HT1")->Fill(ht50,mistag_value*weight);
//           Hist("pT1")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
//           Hist("CSV1")->Fill(maxcsv,mistag_value*weight);
        }
        else
        {
          if (nbtags==2)
          {
            Hist("Mtt2")->Fill(mtt,mistag_value*weight);
            ((TH3F*)Hist("ErrMtt2"))->Fill(mtt,bcc->topjets->at(mistag_index).pt(),maxcsv,weight);
	    Hist("Jet1pT2")->Fill(bcc->topjets->at(ileading).pt(),weight*mistag_value);
	    Hist("Jet2pT2")->Fill(bcc->topjets->at(isubleading).pt(),weight*mistag_value);
	    Hist("Jet1eta2")->Fill(bcc->topjets->at(ileading).eta(),weight*mistag_value);
	    Hist("Jet2eta2")->Fill(bcc->topjets->at(isubleading).eta(),weight*mistag_value);
	    Hist("Jet1csv2")->Fill(leadingcsv,weight*mistag_value);
	    Hist("Jet2csv2")->Fill(subleadingcsv,weight*mistag_value);
//             Hist("MttNoMass2")->Fill(mttNoMass,mistag_value*weight);
//             Hist("HT2")->Fill(ht50,mistag_value*weight);
//             Hist("pT2")->Fill(bcc->topjets->at(mistag_index).pt(),mistag_value*weight);
//             Hist("CSV2")->Fill(maxcsv,mistag_value*weight);
          }
        }
      }
      }//////
    }
  }
  //mass shape
  if (doMassShape)
  {
    
    unsigned int tag_index;
    unsigned int probe_index;
    TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(1).subjets().at(0).eta()*1000000)*100000)));
    if (rand.Uniform(1.)<=0.5)
    {
      tag_index=0;
      probe_index=1;
    }
    else
    {
      tag_index=1;
      probe_index=0;
    } 
    
    double the_mass_shape=TopJetMass(bcc->topjets->at(probe_index));
    //double the_mtt=getMtt(bcc->topjets->at(tag_index),bcc->topjets->at(probe_index));
    double the_pt=bcc->topjets->at(probe_index).pt();
    //double the_ht=getHT50(bcc);
    //if ( HepTopTagWithMatch(bcc->topjets->at(tag_index)) && MassAndPtCutWithMatch(bcc->topjets->at(probe_index)) )
    //{
      
//       if (the_mtt>550) Hist("mass_shape_high")->Fill(the_mass_shape,weight);
//       if (the_mtt<500) Hist("mass_shape_low")->Fill(the_mass_shape,weight);
      //((TH2F*)Hist("mass_shape_ht"))->Fill(the_ht,the_mass_shape,weight);
      //((TH2F*)Hist("mass_shape_pt"))->Fill(the_pt,the_mass_shape,weight);
      //if (the_pt>220) Hist("mass_shape_highpt")->Fill(the_mass_shape,weight);
      //if (the_pt<220) Hist("mass_shape_lowpt")->Fill(the_mass_shape,weight);
    //}
    if ( HepTopTagWithMatch(bcc->topjets->at(tag_index)) && HepTopTagWithMatch(bcc->topjets->at(probe_index)) )
    {
      //Hist("mass_shape")->Fill(TopJetMass(bcc->topjets->at(probe_index)),weight);
      Hist("mass_shape")->Fill(the_mass_shape,weight);
      if (the_pt>220) Hist("mass_shape_high")->Fill(the_mass_shape,weight);
      if (the_pt<220) Hist("mass_shape_low")->Fill(the_mass_shape,weight);
    }
    
    
//     int tag_index=-1;
//     double max_tag_pt=-1;
//     for (unsigned int i=0; i<bcc->topjets->size(); i++)
//     {
//       if ( HepTopTagWithMatch(bcc->topjets->at(i)) )
//       {
//         if (bcc->topjets->at(i).pt()>max_tag_pt)
//         {
//           tag_index=i;
//           max_tag_pt=bcc->topjets->at(i).pt();
//         }
//       }
//     }
//     if (tag_index>-1)
//     {
//       int probe_index=-1;
//       double max_probe_pt=-1;
//       for (unsigned int i=0; i<bcc->topjets->size(); i++)
//       {
//         if (bcc->topjets->at(i).pt()>max_probe_pt && i!=tag_index)
//         {
//           probe_index=i;
//           max_probe_pt=bcc->topjets->at(i).pt();
//         }
//       }
//       if (probe_index>-1)
//       {
//         //Indices={antitag_index,probe_index};
//         // std::vector<float> csv;
//         // csv=bcc->topjets->at(probe_index).btagsub_combinedSecondaryVertex();
//         // float maxcsv = *max_element(std::begin(csv), std::end(csv));
//         // 	float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//         Hist("mass_shape")->Fill(TopJetMass(bcc->topjets->at(probe_index)),weight);
//         // 	Hist("mass_shapeJEC")->Fill(bcc->topjets->at(probe_index).v4().M(),weight);
//         // 	((TH2F*)Hist("mass_shape2D"))->Fill(TopJetMass(bcc->topjets->at(probe_index)),maxcsv,weight);
//       }
//     }
  }
  
  //mistag computation
  if (doMistag && !(isQCD && !isEven) )
  {
    
    
    unsigned int antitag_index=0;
    unsigned int probe_index=0;
    bool isantitagged=false;
    
    //random coin
    TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(0).subjets().at(0).eta()*1000000)*100000)));
    if (rand.Uniform(1.)<=0.5)
    {
      antitag_index=0;
      probe_index=1;
    }
    else
    {
      antitag_index=1;
      probe_index=0;
    }
    
    //double ht50=getHT50(bcc);
    float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
    
//     ////measured mistag
// //     float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//     ((TH3F*)Hist("den_mistagMeasured"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//     if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//     {
//       ((TH3F*)Hist("num_mistagMeasured"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//     }
//     ////
//     
//     ////tagged mistag
//     if(HepTopTagWithMatch(bcc->topjets->at(antitag_index)))
//     {
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagTag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
// 	((TH3F*)Hist("num_mistagTag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }
//     ////
  
    ////minimal inversion mistag
    if( ( !BareHepTopTagWithMatch(bcc->topjets->at(antitag_index)) ) && 
        ( MassAndPtCutWithMatch(bcc->topjets->at(antitag_index)) ) && 
        ( HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(antitag_index))>0.39 ) )
    {
//       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
      ((TH2F*)Hist("den_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
      if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
      {
	((TH2F*)Hist("num_mistag"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,weight);
      }
    }
    ////
    

  
  
    
//     ////R mistag
//     if(HepTopTagInverted(bcc->topjets->at(antitag_index)))
//     {
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagR"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
// 	((TH3F*)Hist("num_mistagR"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }
//     ////
//     
//     ////Rmw mistag
//     if(HepTopTagInverted_mw(bcc->topjets->at(antitag_index)))
//     {
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagRmw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
// 	((TH3F*)Hist("num_mistagRmw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }
//     ////
//     
//     
//     ////Invmw mistag
//      if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(antitag_index)) ) && ( !MassAndPtCutWithMatch(bcc->topjets->at(antitag_index)) ))
//     {
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagInvmw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
//         ((TH3F*)Hist("num_mistagInvmw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }  
//     ////
//     
//     ////Nomw mistag
//      if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(antitag_index)) ) )
//     {
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagNomw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
//         ((TH3F*)Hist("num_mistagNomw"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }  
//     ////
    
//     if ( ( !BareHepTopTagWithMatch(bcc->topjets->at(antitag_index)) ) && ( MassAndPtCutWithMatch(bcc->topjets->at(antitag_index)) ) /*&& ( subJetBTag(bcc->topjets->at(antitag_index),e_CSVM)>0 )*/ )
//     {
// 
// 
//       //       cout<<probe_index<<bcc->topjets->size()<<endl;
//       //       cout<<bcc->topjets->at(probe_index).pt()<<endl;
// //       float maxcsv = getMaxCSV(bcc->topjets->at(probe_index));
//       ((TH3F*)Hist("den_mistagR"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       if (HepTopTagWithMatch(bcc->topjets->at(probe_index)))
//       {
//         ((TH3F*)Hist("num_mistagR"))->Fill(bcc->topjets->at(probe_index).pt(),maxcsv,ht50,weight);
//       }
//     }
  }
  
  if(doMeasured && !(isQCD && !isEven))
  {
    if(HepTopTagWithMatch(bcc->topjets->at(0))&&HepTopTagWithMatch(bcc->topjets->at(1)))
    {
      //double ht50=getHT50(bcc);
      
          HEPTopTaggerReweight httr;
	  double htt_weight=1.0;
	  vector<int> TopJetIndices={0,1};
     /*if (version=="TTbarLept" || version=="TTbarSemi" || version=="TTbarHad")*/ 
     if ((!IsRealData)&&(version.find("QCD")==string::npos))
     {
       if ( (!contains(version,"_httup")) && (!contains(version,"_httdown")) )
       {
	 htt_weight=httr.GetScaleWeight(TopJetIndices);
       }
       if (contains(version,"_httup"))
       {
	 htt_weight=httr.GetScaleWeight(TopJetIndices,"up");
       }
       if (contains(version,"_httdown"))
       {
	 htt_weight=httr.GetScaleWeight(TopJetIndices,"down");
       }
     }
      
      int nbtags=0;
     if (IsRealData)
     {
       if (subJetBTag(bcc->topjets->at(0),e_CSVM)>0) nbtags++;
       if (subJetBTag(bcc->topjets->at(1),e_CSVM)>0) nbtags++;
     }
     else
     {
       if( (!contains(version,"_bcup")) && (!contains(version,"_bcdown")) && (!contains(version,"_lightup")) && (!contains(version,"_lightdown")) )
       {
	 if (subJetBTag(bcc->topjets->at(0),e_CSVM,"mean","/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
	 if (subJetBTag(bcc->topjets->at(1),e_CSVM,"mean","/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
       }
       else
       {
	 int pos=version.rfind("_");
	 string btag_systematic=version.substr(pos+1);
	 btag_systematic+="delta";
	 if (subJetBTag(bcc->topjets->at(0),e_CSVM,btag_systematic,"/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
	 if (subJetBTag(bcc->topjets->at(1),e_CSVM,btag_systematic,"/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZBTagEff.root")>0) nbtags++;
	 
       }
     }

      double mtt=getMtt(bcc->topjets->at(0),bcc->topjets->at(1));
//       double mttJEC=(bcc->topjets->at(0).v4()+bcc->topjets->at(1).v4()).M();
      
//       Hist("MeasuredJECMtt012")->Fill(mttJEC,weight);
      
//       TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(0).subjets().at(0).eta()*1000000)*100000)));
//       unsigned int histo_index;
//       if (rand.Uniform(1.)<=0.5) histo_index=0; else histo_index=1;
//       float maxcsv = getMaxCSV(bcc->topjets->at(histo_index));
      unsigned int ileading = 0;
      unsigned int isubleading = 1;
      if (bcc->topjets->at(1).pt()>bcc->topjets->at(0).pt())
      {
	ileading = 1;
	isubleading = 0;
      }
      float leadingcsv=getMaxCSV(bcc->topjets->at(ileading));
      float subleadingcsv=getMaxCSV(bcc->topjets->at(isubleading));
      
      if (mtt>mttcut)
      {
      Hist("MeasuredMtt012")->Fill(mtt,weight*htt_weight);
      Hist("MeasuredJet1pT012")->Fill(bcc->topjets->at(ileading).pt(),weight*htt_weight);
      Hist("MeasuredJet2pT012")->Fill(bcc->topjets->at(isubleading).pt(),weight*htt_weight);
      Hist("MeasuredJet1eta012")->Fill(bcc->topjets->at(ileading).eta(),weight*htt_weight);
      Hist("MeasuredJet2eta012")->Fill(bcc->topjets->at(isubleading).eta(),weight*htt_weight);
      Hist("MeasuredJet1csv012")->Fill(leadingcsv,weight*htt_weight);
      Hist("MeasuredJet2csv012")->Fill(subleadingcsv,weight*htt_weight);
      
//       Hist("MeasuredHT012")->Fill(ht50,weight);
//       Hist("MeasuredpT012")->Fill(bcc->topjets->at(histo_index).pt(),weight);
//       Hist("MeasuredCSV012")->Fill(maxcsv,weight);
      if (nbtags==0)
      {
        Hist("MeasuredMtt0")->Fill(mtt,weight*htt_weight);
	Hist("MeasuredJet1pT0")->Fill(bcc->topjets->at(ileading).pt(),weight*htt_weight);
	Hist("MeasuredJet2pT0")->Fill(bcc->topjets->at(isubleading).pt(),weight*htt_weight);
	Hist("MeasuredJet1eta0")->Fill(bcc->topjets->at(ileading).eta(),weight*htt_weight);
	Hist("MeasuredJet2eta0")->Fill(bcc->topjets->at(isubleading).eta(),weight*htt_weight);
	Hist("MeasuredJet1csv0")->Fill(leadingcsv,weight*htt_weight);
	Hist("MeasuredJet2csv0")->Fill(subleadingcsv,weight*htt_weight);
	
	
	Hist("Measuredm1")->Fill(TopJetMass(bcc->topjets->at(ileading)),weight*htt_weight);
	Hist("Measuredm2")->Fill(TopJetMass(bcc->topjets->at(isubleading)),weight*htt_weight);
	Hist("MeasuredNjets")->Fill(bcc->jets->size(),weight*htt_weight);
	int nj=0;
	for (unsigned int ii=0; ii<bcc->jets->size(); ii++)
	{
	  if (bcc->jets->at(ii).pt()>50.0) nj++;
	}
	Hist("MeasuredNjets50")->Fill(nj,weight*htt_weight);
	Hist("MeasuredsToppT")->Fill(bcc->topjets->at(0).pt()+bcc->topjets->at(1).pt(),weight*htt_weight);
	if (bcc->jets->size()>3)
	{
	  Hist("MeasuredpT4")->Fill(bcc->jets->at(3).pt(),weight*htt_weight);
	  Hist("MeasuredspT4")->Fill(bcc->jets->at(3).pt()+bcc->jets->at(2).pt()+bcc->jets->at(1).pt()+bcc->jets->at(0).pt(),weight*htt_weight);
	}
	Hist("MeasuredHT50")->Fill(getHT50(bcc),weight*htt_weight);
	((TH2F*)Hist("MeasuredHTT2D1"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(ileading)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(ileading)),weight*htt_weight);
	((TH2F*)Hist("MeasuredHTT2D2"))->Fill(HepTopTagPairwiseMassWithMatch1(bcc->topjets->at(isubleading)),HepTopTagPairwiseMassWithMatch2(bcc->topjets->at(isubleading)),weight*htt_weight);
	
	if (bcc->jets->size()>4)
	{
	  Hist("MeasuredpT5")->Fill(bcc->jets->at(4).pt(),weight*htt_weight);
	  Hist("MeasuredspT5")->Fill(bcc->jets->at(4).pt()+bcc->jets->at(3).pt()+bcc->jets->at(2).pt()+bcc->jets->at(1).pt()+bcc->jets->at(0).pt(),weight*htt_weight);
	}

//         Hist("MeasuredJECMtt0")->Fill(mttJEC,weight);
//         Hist("MeasuredHT0")->Fill(ht50,weight);
//         Hist("MeasuredpT0")->Fill(bcc->topjets->at(histo_index).pt(),weight);
//         Hist("MeasuredCSV0")->Fill(maxcsv,weight);
      }
      else
      {
        if (nbtags==1)
        {
          Hist("MeasuredMtt1")->Fill(mtt,weight*htt_weight);
	  Hist("MeasuredJet1pT1")->Fill(bcc->topjets->at(ileading).pt(),weight*htt_weight);
	  Hist("MeasuredJet2pT1")->Fill(bcc->topjets->at(isubleading).pt(),weight*htt_weight);
	  Hist("MeasuredJet1eta1")->Fill(bcc->topjets->at(ileading).eta(),weight*htt_weight);
	  Hist("MeasuredJet2eta1")->Fill(bcc->topjets->at(isubleading).eta(),weight*htt_weight);
	  Hist("MeasuredJet1csv1")->Fill(leadingcsv,weight*htt_weight);
	  Hist("MeasuredJet2csv1")->Fill(subleadingcsv,weight*htt_weight);
	  
//           Hist("MeasuredJECMtt1")->Fill(mttJEC,weight);
//           Hist("MeasuredHT1")->Fill(ht50,weight);
//           Hist("MeasuredpT1")->Fill(bcc->topjets->at(histo_index).pt(),weight);
//           Hist("MeasuredCSV1")->Fill(maxcsv,weight);
        }
        else
        {
          if (nbtags==2)
          {
            Hist("MeasuredMtt2")->Fill(mtt,weight*htt_weight);
	    Hist("MeasuredJet1pT2")->Fill(bcc->topjets->at(ileading).pt(),weight*htt_weight);
	    Hist("MeasuredJet2pT2")->Fill(bcc->topjets->at(isubleading).pt(),weight*htt_weight);
	    Hist("MeasuredJet1eta2")->Fill(bcc->topjets->at(ileading).eta(),weight*htt_weight);
	    Hist("MeasuredJet2eta2")->Fill(bcc->topjets->at(isubleading).eta(),weight*htt_weight);
	    Hist("MeasuredJet1csv2")->Fill(leadingcsv,weight*htt_weight);
	    Hist("MeasuredJet2csv2")->Fill(subleadingcsv,weight*htt_weight);
	    
//             Hist("MeasuredJECMtt2")->Fill(mttJEC,weight);
//             Hist("MeasuredHT2")->Fill(ht50,weight);
//             Hist("MeasuredpT2")->Fill(bcc->topjets->at(histo_index).pt(),weight);
//             Hist("MeasuredCSV2")->Fill(maxcsv,weight);
          }
        }
      }
      }////
    }
    
//     if(HepTopTag(bcc->toptagjets->at(0))&&HepTopTag(bcc->toptagjets->at(1)))
//     {
//       int nbtags=0;
//       if (subJetBTag(bcc->toptagjets->at(0),e_CSVM)>0) nbtags++;
//       if (subJetBTag(bcc->toptagjets->at(1),e_CSVM)>0) nbtags++;
//       double mtt=getMtt(bcc->toptagjets->at(0),bcc->toptagjets->at(1));
//       double mttJEC=(bcc->toptagjets->at(0).v4()+bcc->toptagjets->at(1).v4()).M();
//       Hist("MeasuredHTTMtt012")->Fill(mtt,weight);
//       Hist("MeasuredHTTJECMtt012")->Fill(mttJEC,weight);
//       TRandom3 rand(abs(static_cast<int>(sin(bcc->topjets->at(0).subjets().at(0).eta()*1000000)*100000)));
//       unsigned int histo_index;
//       if (rand.Uniform(1.)<=0.5) histo_index=0; else histo_index=1;
//       Hist("MeasuredHTTHT012")->Fill(getHT50(bcc),weight);
//       Hist("MeasuredHTTpT012")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
//       Hist("MeasuredHTTCSV012")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
//       if (nbtags==0)
//       {
//         Hist("MeasuredHTTMtt0")->Fill(mtt,weight);
//         Hist("MeasuredHTTJECMtt0")->Fill(mttJEC,weight);
//         Hist("MeasuredHTTHT0")->Fill(getHT50(bcc),weight);
//         Hist("MeasuredHTTpT0")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
//         Hist("MeasuredHTTCSV0")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
//       }
//       else
//       {
//         if (nbtags==1)
//         {
//           Hist("MeasuredHTTMtt1")->Fill(mtt,weight);
//           Hist("MeasuredHTTJECMtt1")->Fill(mttJEC,weight);
//           Hist("MeasuredHTTHT1")->Fill(getHT50(bcc),weight);
//           Hist("MeasuredHTTpT1")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
//           Hist("MeasuredHTTCSV1")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
//         }
//         else
//         {
//           if (nbtags==2)
//           {
//             Hist("MeasuredHTTMtt2")->Fill(mtt,weight);
//             Hist("MeasuredHTTJECMtt2")->Fill(mttJEC,weight);
//             Hist("MeasuredHTTHT2")->Fill(getHT50(bcc),weight);
//             Hist("MeasuredHTTpT2")->Fill(bcc->toptagjets->at(histo_index).pt(),weight);
//             Hist("MeasuredHTTCSV2")->Fill(getMaxCSV(bcc->toptagjets->at(histo_index)),weight);
//           }
//         }
//       }
      
      //AK5 code
//       vector<unsigned int> ak5indices;
//       LorentzVector ak5v4(0,0,0,0);
//       int topjet0ak5count=0;
//       int topjet1ak5count=0;
//       int nak5btag=0;
//       bool istopjet0ak5btag=false;
//       bool istopjet1ak5btag=false;
//       bool isgood=true;
//       for(unsigned int iak5=0; iak5<bcc->jets->size(); iak5++)
//       {
//         if (topjet0ak5count<=3)
//         {
//           if (bcc->toptagjets->at(0).deltaR(bcc->jets->at(iak5))<1.5)
//           {
//             ak5v4=ak5v4+bcc->jets->at(iak5).v4();
//             topjet0ak5count++;
//             ak5indices.push_back(iak5);
//           }
//         }
//         if (topjet1ak5count<=3)
//         {
//           if (bcc->toptagjets->at(1).deltaR(bcc->jets->at(iak5))<1.5)
//           {
//             ak5v4=ak5v4+bcc->jets->at(iak5).v4();
//             topjet1ak5count++;
//             ak5indices.push_back(iak5);
//           }
//         }
//       }
//       if (istopjet0ak5btag) nak5btag++;
//       if (istopjet1ak5btag) nak5btag++;
//       for(unsigned int ch1=0; ch1<ak5indices.size()-1; ch1++)
//       {
//         for(unsigned int ch2=ch1+1; ch2<ak5indices.size(); ch2++)
//         {
//           if (ak5indices[ch1]==ak5indices[ch2])
//           {
//             isgood=false;
//             cout<<ak5indices[ch1]<<" not good\n";
//           }
//         }
//       }
//       if (isgood)
//       {
//         double mttAK5=ak5v4.M();
//         Hist("MeasuredAK5Mtt012")->Fill(mttAK5,weight);
//         if (nak5btag==0)
//         {
//           Hist("MeasuredAK5Mtt0")->Fill(mttAK5,weight);
//         }
//         else
//         {
//           if (nak5btag==1)
//           {
//             Hist("MeasuredAK5Mtt1")->Fill(mttAK5,weight);
//           }
//           else
//           {
//             if (nak5btag==2)
//             {
//               Hist("MeasuredAK5Mtt2")->Fill(mttAK5,weight);
//             }
//           }
//         }
//       }
//    }
    
  }
  
}


void BackgroundHists::Finish()
{
  delete mistag,mistagmc,shape,mjmistag,mjmistagmc,mjshape;
  f->Close();
  delete f;
}

