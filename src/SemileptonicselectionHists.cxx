#include "include/SemileptonicselectionHists.h"
#include <iostream>

using namespace std;

SemileptonicselectionHists::SemileptonicselectionHists(const char* name) : BaseHists(name)
{
  // named default constructor
   
}

SemileptonicselectionHists::~SemileptonicselectionHists()
{
  // default destructor, does nothing
}

void SemileptonicselectionHists::Init()
{
  // book all histograms here

 // m_tpr = new TopPtReweight();
  
  double jetpt_bbins[] = {
    20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800, 1600
  };

  Book( TH1F( "N_topjets", ";N^{jets};Events", 20, 0, 20 ) );
  Book( TH1F( "N_mu", ";N^{muons};Events", 5, 0, 5 ) );
  Book( TH1F( "N_pv", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_pv200", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_pv300", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_pv400", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_pv500", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_pv600", ";N^{PV};Events", 50, 0, 50 ) );
  Book( TH1F( "N_events_perLumiBin", ";N^{evt};Events", 24, 0, 24 ) );
  Book( TH1F( "N_pv_perLumiBin", ";N^{PV};Events", 24, 0, 24 ) );
  Book( TH1D( "DR_Mub", ";DR muon-b;Events", 100, 0, 6.28));
  Book( TH1D( "DPhi_Mub", ";DPhi muon-b;Events", 100, 0, 6.28));
  Book( TH1D( "DR_Mutop", ";DR muon-top;Events", 100, 0, 6.28));
  Book( TH1D( "DPhi_Mutop", ";DPhi muon-top;Events", 100, 0, 6.28));
  Book( TH1D( "DR_btop", ";DR b-top;Events", 100, 0, 6.28));
  Book( TH1D( "DPhi_btop", ";DPhi b-top;Events", 100, 0, 6.28));
  Book( TH1D( "MassTop", ";Top jet mass (GeV);Events", 50, 0, 500));
  Book( TH1D( "Pt_b_sub", ";Pt b-subjet (GeV);Events", 17, jetpt_bbins));
  Book( TH1D( "Pt_nonb_sub", ";Pt non-b-subjet (GeV);Events", 17, jetpt_bbins));
  Book( TH1D( "Pt_tagged_sub", ";Pt non-b-subjet (GeV);Events", 17, jetpt_bbins));
  Book( TH1D( "Pt_all_sub", ";Pt all subjets (GeV);Events", 17, jetpt_bbins));
  Book( TH1D( "Pt_all_sub_nobin", ";Pt all subjets (GeV);Events", 40, 0, 500));
  Book( TH1D( "Toppt", ";Pt top-jet (GeV);Events", 25, 0, 1000));
  double PT_bins[] = {0,40,80,120,160,200,240,280,320,360,400,500,600,1000};
  Book( TH1D( "Toppt_2", ";Pt top-jet (GeV);Events", sizeof(PT_bins)/sizeof(double)-1,PT_bins));
  
  double PT_bins2[] = {0,400,600,800,1000,10000};
  Book( TH1D( "Toppt_3", ";Pt top-jet (GeV);Events", sizeof(PT_bins2)/sizeof(double)-1,PT_bins2));
  
  Book( TH1D( "m01", ";Inv mass of subjets 0+1 (GeV);Events", 100, 0, 500));
  Book( TH1D( "m02", ";Inv mass of subjets 0+2 (GeV);Events", 100, 0, 500));
  Book( TH1D( "m12", ";Inv mass of subjets 1+2 (GeV);Events", 100, 0, 500));
  Book( TH1D( "mW", ";Inv mass of W (GeV);Events", 100, 0, 500));
  Book( TH1D( "m012", ";Inv mass of subjets 0+1+2 (GeV);Events", 50, 0, 500));
  
  Book( TH1D( "Nevts", ";Passed;Events", 1, 0, 1));
  
  Book( TH1D( "mMuB", ";Inv mass Mu + Btagged jet (GeV);Events", 100, 0, 500));
  Book( TH1D( "dRMuB", ";DeltaR Mu Btagged jet;Events", 100, 0, 2));

  Book( TH1F( "TopPtWeightHisto","TopPtWeightHisto;Weight;Events",500,0.5,2));
  Book( TH1F( "TopPtFullWeightHisto","TopPtFullWeightHisto;Weight;Events",500,0,0.5));
  Book( TH2F( "TopWeightVsPtHisto","TopWeightVsPtHisto;Weight;pT(GeV)",500,0.5,2,100,0,1000));
  Book( TH2F( "TopWeightVsGenPtHisto","TopWeightVsGenPtHisto;Weight;pT(GeV)",500,0.5,2,100,0,1000));
  Book( TH1F( "EventCount","EventCount;before - after;Events",2,0,2));
  
  double SF_bins[] = {150,200,250,400,10000};
  Book( TH1D("ptSFcount","ptSFcount;pT [GeV];Events",sizeof(SF_bins)/sizeof(double)-1,SF_bins));

  Book( TH1D( "var1_HTT", ";atan(m_{13}/m_{12});Events",50 ,0. ,1.5 ));
  Book( TH1D( "var2_HTT", ";m_{23}/m_{123};Events",50 ,0. ,1. ));
  Book( TH1D( "var3_HTT", ";m_{W};Events", 50, 0, 150));
  Book( TH2D( "HTT2D", ";atan(m_{13}/m_{12});m_{23}/m_{123}",100 ,0. ,1.5, 100,0. ,1.));
  Book( TH1D( "dRsubjet", ";DeltaR(subjets);Events", 200, 0, 3));
  Book( TH1D( "LeptToppt", ";Pt leptonic top (GeV);Events", 25, 0, 1000));
}

void SemileptonicselectionHists::Fill()
{
  // fill the histograms
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  LuminosityHandler* lumih = calc->GetLumiHandler();

  
  // important: get the event weight
  double weight = calc->GetWeight();
  //cout<<m_tpr->GetScaleWeight()<<endl;
  //std::cout<<weight<<std::endl;
//   double ptreweight=m_tpr->GetScaleWeight();
//   if (!IsRealData)
//   {
//     TH2F* TopWeightVsGenPtHisto = (TH2F*)Hist( "TopWeightVsGenPtHisto");
//     TTbarGen* Decay = calc->GetTTbarGen();
//     GenParticle topgen=Decay->Top();
//     GenParticle antitopgen=Decay->Antitop();
// //     TopWeightVsGenPtHisto->Fill(ptreweight,topgen.pt(),1);
// //     TopWeightVsGenPtHisto->Fill(ptreweight,antitopgen.pt(),1);
//   }
  int tprindex = findTheHighestPtGoodTopJet(bcc);
  double GoodTopJetPt = -100;
  if (tprindex>-1) GoodTopJetPt = bcc->toptagjets->at(tprindex).pt();
//   Hist( "TopPtWeightHisto")->Fill(ptreweight);
  Hist( "TopPtFullWeightHisto")->Fill(weight);
  TH2F* TopWeightVsPtHisto = (TH2F*)Hist( "TopWeightVsPtHisto");
//   if (tprindex>-1) TopWeightVsPtHisto->Fill(ptreweight,GoodTopJetPt,1);
  
  if (tprindex>-1) Hist("ptSFcount")->Fill(GoodTopJetPt,weight);
  Hist( "EventCount")->Fill(0.1,weight);
  
  int run = calc->GetRunNum();
  int lumiblock = calc->GetLumiBlock();
  int Npvs = calc->GetPrimaryVertices()->size();


  Hist("Nevts")->Fill(0.1,weight);
  
  ///////////////////////////////////////
  if (bcc->muons->size()==0) return;
  ///////////////////////////////////////
  
  
//   if(!IsRealData){
//   //Filling generator-level information for semi-leptonic ttbar events
//   TTbarGen* Decay = calc->GetTTbarGen();
// 
//   GenParticle topgen=Decay->Top();
//   GenParticle antitopgen=Decay->Antitop();
//   GenParticle btop=Decay->bTop();
//   GenParticle bantitop=Decay->bAntitop();
//   int decaytop=abs(Decay->Wdecay1().pdgId());
//   int decayantitop=abs(Decay->WMinusdecay1().pdgId());
//   int semileptop=0;
//   int semilepantitop=0;
//   GenParticle muongen;
// 
//   if((decaytop==13||decaytop==14)&&decayantitop>0&&decayantitop<=5){
//     semileptop=1;
//     if(decaytop==13){
//       muongen=Decay->Wdecay1();
//     }
//     if(decaytop==14){
//       muongen=Decay->Wdecay2();
//     }
//   }
//   if((decayantitop==13||decayantitop==14)&&decaytop>0&&decaytop<=5){
//     semilepantitop=1;
//     if(decayantitop==13){
//       muongen=Decay->WMinusdecay1();
//     }
//     if(decaytop==14){
//       muongen=Decay->WMinusdecay2();
//     }
//   }
// 
//   if(semileptop){
//     Hist("DR_Mub")->Fill(muongen.deltaR(btop),weight);
//     Hist("DPhi_Mub")->Fill(muongen.deltaPhi(btop),weight);
//     Hist("DR_Mutop")->Fill(muongen.deltaR(antitopgen),weight);
//     Hist("DPhi_Mutop")->Fill(muongen.deltaPhi(antitopgen),weight);
//     Hist("DR_btop")->Fill(btop.deltaR(antitopgen),weight);
//     Hist("DPhi_btop")->Fill(btop.deltaPhi(antitopgen),weight);
//   }
// 
//   if(semilepantitop){
//     Hist("DR_Mub")->Fill(muongen.deltaR(bantitop),weight);
//     Hist("DPhi_Mub")->Fill(muongen.deltaPhi(bantitop),weight);
//     Hist("DR_Mutop")->Fill(muongen.deltaR(topgen),weight);
//     Hist("DPhi_Mutop")->Fill(muongen.deltaPhi(topgen),weight);
//     Hist("DR_btop")->Fill(bantitop.deltaR(topgen),weight);
//     Hist("DPhi_btop")->Fill(bantitop.deltaPhi(topgen),weight);
//   }
// 
//   }//if Monte Carlo

  Hist("N_pv")->Fill(Npvs, weight);
  
  if(calc->IsRealData()){  
    Hist( "N_pv_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), Npvs*weight);
  Hist( "N_events_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), weight);
  }

  //double npu = bcc.genInfo->pileup_TrueNumInteractions();
  //if(npu>50) npu=49.9999;
  //Hist( "N_pileup_hist" )->Fill( npu, weight );

  //MET* met = calc->GetMET();
  //Hist("MET_lx")->Fill(met->pt(), weight);

  //double HT = calc->GetHT();
  //Hist("HT_lx")->Fill(HT, weight);

  //double HTlep = calc->GetHTlep();
  //Hist("HTlep_lx")->Fill(HTlep, weight);

  int Ntopjets = bcc->toptagjets->size();
  Hist("N_topjets")->Fill(Ntopjets, weight);
  std::vector<Muon>* muons = calc->GetMuons();
  int Nmuons = muons->size();
  Hist("N_mu")->Fill(Nmuons, weight);

  //for (int i=0; i<Nmuons; ++i){
  //Muon thismu = muons->at(i);
  //Hist("pt_mu_lx")->Fill(thismu.pt(), weight);
  //Hist("eta_mu")->Fill(thismu.eta(), weight);
  //Hist("reliso_mu")->Fill(thismu.relIso(), weight);
  //}

  float _maxpt=-1;
  float _theinvmass=-1;
  int _theindex=-1;
  for(unsigned int i=0; i<bcc->jets->size(); ++i) 
  {
    Jet jet = bcc->jets->at(i);
    Muon muon = bcc->muons->at(0);
    bool isbtagged=false;
    //if(m_type==e_CSVL && jet.btag_combinedSecondaryVertex()>0.244) isbtagged=true;
    if(jet.btag_combinedSecondaryVertex()>0.679) isbtagged=true;
    //if(m_type==e_CSVT && jet.btag_combinedSecondaryVertex()>0.898) isbtagged=true;
    /*if(m_type==e_JPL && jet.btag_jetProbability()>0.275) isbtagged=true;
    if(m_type==e_JPM && jet.btag_jetProbability()>0.545) isbtagged=true;
    if(m_type==e_JPT && jet.btag_jetProbability()>0.790) isbtagged=true;*/
    double deltaPhi = jet.deltaR( muon );
    double invmass = 0; if (( jet.v4() + muon.v4() ).isTimelike()) invmass=( jet.v4() + muon.v4() ).M();
//    bool masswindow = ( ( invmass > m_min_mass ) && ( invmass < m_max_mass ) );
    if(jet.pt()>200. && fabs(jet.eta())<2.5 && deltaPhi<PI/2 && isbtagged && jet.pt()>_maxpt/*&& masswindow*/)
    {
      _theinvmass=invmass;
      _maxpt=jet.pt();
      _theindex=i;
    }
  }
  if (_theindex>-1)
  {
   Hist("mMuB")->Fill(_theinvmass,weight);
   Hist("dRMuB")->Fill(bcc->jets->at(_theindex).deltaR(bcc->muons->at(0)),weight);
  }
  
  std::vector<Particle> subjets_top;
  std::vector<float> btagsub_combinedSecondaryVertex_top;
  std::vector<int> flavorsub_top;
  
  /*double limpt=0;
  int indexjet=-99999;

  int countjets=0;

  std::vector<Particle> subjets_top;
  std::vector<float> btagsub_combinedSecondaryVertex_top;
  std::vector<int> flavorsub_top;

  for(unsigned int i=0; i<bcc->toptagjets->size(); ++i) {
    int jettagged=0;
    
    subjets_top=bcc->toptagjets->at(i).subjets();
    btagsub_combinedSecondaryVertex_top=bcc->toptagjets->at(i).btagsub_combinedSecondaryVertex();
    
    for(unsigned int j=0; j < btagsub_combinedSecondaryVertex_top.size(); ++j){
      
      float test=btagsub_combinedSecondaryVertex_top[j];

      //if(test>0.244) jettagged=1;
      if(test>0.679) jettagged=1;
      //if(test>0.898) jettagged=1;
      
    }

    //jettagged=0;

    //if(HepTopTag(bcc->toptagjets->at(i))){

	// jettagged=1;

    //}
      
    if(bcc->muons->size()>0){
      double deltaphi=bcc->toptagjets->at(i).deltaPhi(bcc->muons->at(0));
    
      if(jettagged&&(deltaphi>(2*PI/3))&&(bcc->toptagjets->at(i).pt()>150.)&&(fabs(bcc->toptagjets->at(i).eta())<2.5)){
	
	countjets=countjets+1;

	if(bcc->toptagjets->at(i).pt()>limpt){

	  indexjet=i;
	  limpt=bcc->toptagjets->at(i).pt();

	}
    
      }
    }
}//loop over top jets
*/
  
  
      int goodleptjetindex=-1;
      float maxleptjetpt=-1;

    //Assumes to have only one muon

    for(unsigned int i=0; i<bcc->jets->size(); ++i) {
      int jettagged=0;
      if(bcc->jets->at(i).btag_combinedSecondaryVertex()>0.679) jettagged=1;

      double deltaphi=bcc->jets->at(i).deltaR(bcc->muons->at(0));
      
      if(jettagged&&(deltaphi<(PI/2))&&(bcc->jets->at(i).pt()>30.0)&&(fabs(bcc->jets->at(i).eta())<2.4)&&(bcc->jets->at(i).pt()>maxleptjetpt)){

	goodleptjetindex=i;
	maxleptjetpt=bcc->jets->at(i).pt();

      }

    }
  if(goodleptjetindex>-1)
  {
    LorentzVector lepttop(0,0,0,0); 
    lepttop+=bcc->jets->at(goodleptjetindex).v4();
    lepttop+=bcc->muons->at(0).v4();
    lepttop+=bcc->met->v4();
    //if(lepttop.isTimelike()) 
    //{
    Hist("LeptToppt")->Fill(lepttop.Pt(),weight);
    //}
    //else
    //{
    //  Hist("LeptToppt")->Fill(0.,weight);
    //}

  }
  
  
  
  
  int indexjet=findTheHighestPtGoodTopJet(bcc);
    
  
  if(indexjet>-1){
  
    if (bcc->toptagjets->at(indexjet).pt()>200.0)
    {
      Hist("N_pv200")->Fill(Npvs, weight);
      if (bcc->toptagjets->at(indexjet).pt()>300.0)
      {
	Hist("N_pv300")->Fill(Npvs, weight);
	if (bcc->toptagjets->at(indexjet).pt()>400.0)
	{
	  Hist("N_pv400")->Fill(Npvs, weight);
	  if (bcc->toptagjets->at(indexjet).pt()>500.0)
	  {
	    Hist("N_pv500")->Fill(Npvs, weight);
	    if (bcc->toptagjets->at(indexjet).pt()>600.0)
	    {
	      Hist("N_pv600")->Fill(Npvs, weight);
	    }
	  }
	}
      }
    }
    
    LorentzVector allsubjets(0,0,0,0);
    double mjet=0;
    double m012=0;

    for(unsigned int j=0; j < 3; ++j){
        allsubjets += bcc->toptagjets->at(indexjet).subjets()[j].v4();
    }
    if(!allsubjets.isTimelike()) {
        m012=0;
    }
    else{
      m012 = allsubjets.M();
    }
    //Hist("Nevts")->Fill(0.1,weight);
    //uncomments to have mass jet from jet and not from sum subjets
     if(bcc->toptagjets->at(indexjet).v4().isTimelike())
    mjet=bcc->toptagjets->at(indexjet).v4().M(); else mjet=0;
    Hist("MassTop")->Fill(mjet,weight);
    Hist("m012")->Fill(m012,weight);

    Hist("Toppt")->Fill(bcc->toptagjets->at(indexjet).pt(),weight);
    Hist("Toppt_2")->Fill(bcc->toptagjets->at(indexjet).pt(),weight);
    Hist("Toppt_3")->Fill(bcc->toptagjets->at(indexjet).pt(),weight);

    subjets_top=bcc->toptagjets->at(indexjet).subjets();
    btagsub_combinedSecondaryVertex_top=bcc->toptagjets->at(indexjet).btagsub_combinedSecondaryVertex();
    flavorsub_top=bcc->toptagjets->at(indexjet).flavorsub();
    for(unsigned int j=0; j < btagsub_combinedSecondaryVertex_top.size(); ++j){
      
      //if(j==0){
      Hist("Pt_all_sub")->Fill(subjets_top[j].pt(),weight);
      Hist("Pt_all_sub_nobin")->Fill(subjets_top[j].pt(),weight);
      //}
      if(btagsub_combinedSecondaryVertex_top[j]>0.679)//{
      
	Hist("Pt_tagged_sub")->Fill(subjets_top[j].pt(),weight);

	if(abs(flavorsub_top[j])==5) Hist("Pt_b_sub")->Fill(subjets_top[j].pt(),weight);
	if(abs(flavorsub_top[j])!=5) Hist("Pt_nonb_sub")->Fill(subjets_top[j].pt(),weight);
      }//loop on subjets

      //heptoptagger variable plots
      if(btagsub_combinedSecondaryVertex_top.size()>=3) 
      {
	//std::cout<<"subjet0:"<<btagsub_combinedSecondaryVertex_top[0]<<" subjet1:"<<btagsub_combinedSecondaryVertex_top[1]<<" subjet2:"<<btagsub_combinedSecondaryVertex_top[2]<<std::endl;
	std::vector<Particle> subjets = bcc->toptagjets->at(indexjet).subjets();
	
	double mW = 0;
	if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
	{
	  mW=(subjets[0].v4()+subjets[1].v4()).M();
	  Hist("mW")->Fill(mW,weight);
	}
	
	sort(subjets.begin(), subjets.end(), HigherPt());
	
	double m01 = 0;
	if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
	{
	  m01=(subjets[0].v4()+subjets[1].v4()).M();
	  Hist("m01")->Fill(m01,weight);
	}
	double m02 = 0;
	if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
	{
	  m02=(subjets[0].v4()+subjets[2].v4()).M();
	  Hist("m02")->Fill(m02,weight);
	}
	double m12 = 0;
	if( (subjets[1].v4()+subjets[2].v4()).isTimelike() )
	{
	  m12 = (subjets[1].v4()+subjets[2].v4()).M();
	  Hist("m12")->Fill(m12,weight);
	}
	double m12_HTT = m01;
	double m13_HTT = m02;
	double m23_HTT = m12;
	double m123_HTT = m012;
	double var1_HTT = atan(m13_HTT/m12_HTT);
	double var2_HTT = m23_HTT/m123_HTT;
	double var3_HTT = mW;
	Hist("var1_HTT")->Fill(var1_HTT,weight);
	Hist("var2_HTT")->Fill(var2_HTT,weight);
	Hist("var3_HTT")->Fill(var3_HTT,weight);
	TH2D * HTT2D = (TH2D*)Hist("HTT2D");
	HTT2D->Fill(var1_HTT,var2_HTT,weight);
	Hist("dRsubjet")->Fill(subjets[0].deltaR(subjets[1]),weight);
	Hist("dRsubjet")->Fill(subjets[1].deltaR(subjets[2]),weight);
	Hist("dRsubjet")->Fill(subjets[0].deltaR(subjets[2]),weight);
      }//heptoptagger variable plots
      
 //   }
    
  }
  
}

void SemileptonicselectionHists::Finish()
{
  // final calculations, like division and addition of certain histograms
  EventCalc* calc = EventCalc::Instance();
  bool IsRealData = calc->IsRealData();
  if (IsRealData){
    Hist("N_pv_perLumiBin")->Divide( Hist("N_pv_perLumiBin"), Hist("N_events_perLumiBin"));
    Hist( "N_pv_perLumiBin")->GetYaxis()->SetTitle("Events/Lumi");
  }

}

