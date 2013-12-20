#include <iostream>

using namespace std;

// Local include(s):
#include "include/SemileptonicselectionHists.h"
#include "include/BTagEffHistsHadTop.h"
#include "include/SemileptonicHepTopTagValSelCycle.h"
// #include "include/SelectionModules.h"
// #include "include/ObjectHandler.h"
// #include "JetCorrectorParameters.h"
#include "SFrameAnalysis/include/SelectionModules.h"

ClassImp( SemileptonicHepTopTagValSelCycle );

SemileptonicHepTopTagValSelCycle::SemileptonicHepTopTagValSelCycle()
    : AnalysisCycle()
{

    // constructor, declare additional variables that should be
    // obtained from the steering-xml file

    // set the integrated luminosity per bin for the lumi-yield control plots
    SetIntLumiPerBin(25.);

    DeclareProperty( "ValidationType", m_ValidationType );

    DeclareProperty( "CSVOperatingPoint", m_CSVOperatingPoint );
    DeclareProperty( "BTagEffi_Filename_MC" , m_BTagEffiFilenameMC);
    DeclareProperty( "BTaggingMode" , m_BTaggingMode);
    runs.clear();
    lumis.clear();
    evnums.clear();
    
}

SemileptonicHepTopTagValSelCycle::~SemileptonicHepTopTagValSelCycle()
{
    // destructor
}

void SemileptonicHepTopTagValSelCycle::BeginCycle() throw( SError )
{
    // Start of the job, general set-up and definition of
    // objects are done here

    // Important: first call BeginCycle of base class
    AnalysisCycle::BeginCycle();

    return;

}

void SemileptonicHepTopTagValSelCycle::EndCycle() throw( SError )
{
    // clean-up, info messages and final calculations after the analysis
    for (unsigned int i=0;i<runs.size();i++)
    {
      cout<<runs[i]<<":"<<lumis[i]<<":"<<evnums[i]<<endl;
    }

    // call the base cycle class for all standard methods
    // and a summary of the made selections
    AnalysisCycle::EndCycle();

    return;

}

void SemileptonicHepTopTagValSelCycle::BeginInputData( const SInputData& id ) throw( SError )
{
    // declaration of histograms and selections

    // Important: first call BeginInputData of base class
    AnalysisCycle::BeginInputData( id );

    std::vector<JetCorrectorParameters> pars;
    std::vector<JetCorrectorParameters> parsTopJet;

    //see https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#GetTxtFiles how to get the txt files with jet energy corrections from the database
    if(!addGenInfo()) {
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L1FastJet_" + m_JECJetCollection + ".txt"));
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2Relative_" + m_JECJetCollection + ".txt"));
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L3Absolute_" + m_JECJetCollection + ".txt"));
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2L3Residual_" + m_JECJetCollection + ".txt"));
    } else {
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L1FastJet_" + m_JECJetCollection + ".txt"));
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L2Relative_" + m_JECJetCollection + ".txt"));
        pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L3Absolute_" + m_JECJetCollection + ".txt"));
    }
    if(!addGenInfo()) {
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L1FastJet_" + m_JECTopJetCollection + ".txt"));
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2Relative_" + m_JECTopJetCollection + ".txt"));
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L3Absolute_" + m_JECTopJetCollection + ".txt"));
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2L3Residual_" + m_JECTopJetCollection + ".txt"));
    } else {
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L1FastJet_" + m_JECTopJetCollection + ".txt"));
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L2Relative_" + m_JECTopJetCollection + ".txt"));
        parsTopJet.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L3Absolute_" + m_JECTopJetCollection + ".txt"));
    }

    m_corrector = new FactorizedJetCorrector(pars);
    m_correctorTopJet = new FactorizedJetCorrector(parsTopJet);
    
    /*TopPtWeightHisto = new TH1D("TopPtWeightHisto","TopPtWeightHisto;Weight;Events",500,0.5,2);
    TopPtFullWeightHisto = new TH1D("TopPtFullWeightHisto","TopPtFullWeightHisto;Weight;Events",500,0.5,2);
    TopWeightVsPtHisto = new TH2D("TopWeightVsPtHisto","TopWeightVsPtHisto;Weight;pT(GeV)",500,0.5,2,100,0,1000);
    TopWeightVsGenPtHisto = new TH2D("TopWeightVsGenPtHisto","TopWeightVsGenPtHisto;Weight;pT(GeV)",500,0.5,2,100,0,1000);
    EventCount = new TH1D("EventCount","EventCount;before - after;Events",2,0,2);*/
    
    
    //do b tag
    
    bool dobtag = false;
    if(m_BTagEffiFilenameMC.size()>0)
    {
      if(id.GetVersion()=="TTbar" || id.GetVersion()=="TTbarsemi_powheg" || id.GetVersion()=="TTbarlept_powheg" || id.GetVersion()=="TTbarsemi_mcatnlo" || id.GetVersion()=="TTbarlept_mcatnlo")
      {
	m_BTagEffiFilenameMC="/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/preselection/SemileptonicPreselectionCycle";
      }
      m_BTagEffiFilenameMC += ".";
      m_BTagEffiFilenameMC += id.GetType();
      m_BTagEffiFilenameMC += ".";
      m_BTagEffiFilenameMC += id.GetVersion();
      m_BTagEffiFilenameMC += ".root";
      dobtag=true;
    }

    if(id.GetType()=="DATA" || id.GetType()=="Data" || id.GetType()=="data") dobtag=false;

    m_bsf = NULL;
   
    if(dobtag)
    {
      std::cout << m_BTagEffiFilenameMC << std::endl;
      m_bsf = new BTaggingRoutineTopTag(atof(m_CSVOperatingPoint.c_str()), m_BTaggingMode, m_BTagEffiFilenameMC);
    }
    
    //m_tpr = new TopPtReweight();
    
    
    
    // -------------------- set up the selections ---------------------------
   /*
    Selection* trigger = new Selection("trigger");

    trigger->addSelectionModule(new TriggerSelection("HLT_IsoMu40_eta2p1"));

    RegisterSelection(trigger);

    Selection* preselectionNPrimaryVertexSelection = new Selection("preselectionNPrimaryVertexSelection");
    Selection* preselectionNElectronSelection = new Selection("preselectionNElectronSelection");
    Selection* preselectionNMuonSelection = new Selection("preselectionNMuonSelection");
    Selection* preselectionNJetSelection = new Selection("preselectionNJetSelection");//at least two jets with pt>30GeV and eta<2.5
    Selection* preselectionNTopJetSelection = new Selection("preselectionNTopJetSelection");//at least one jet with pt>150GeV and eta<2.5
    
    //Selection* preselection = new Selection("preselection");

    preselectionNPrimaryVertexSelection->addSelectionModule(new NPrimaryVertexSelection(1));
    preselectionNElectronSelection->addSelectionModule(new NElectronSelection(0,0));
    preselectionNMuonSelection->addSelectionModule(new NMuonSelection(1,1));
    preselectionNJetSelection->addSelectionModule(new NJetSelection(2,int_infinity(),30.,2.5));//at least two jets with pt>30GeV and eta<2.5
    preselectionNTopJetSelection->addSelectionModule(new NTopJetSelection(1,int_infinity(),150.,2.5));//at least one jet with pt>150GeV and eta<2.5

    RegisterSelection(preselectionNPrimaryVertexSelection);
    RegisterSelection(preselectionNElectronSelection);
    RegisterSelection(preselectionNMuonSelection);
    RegisterSelection(preselectionNJetSelection);
    RegisterSelection(preselectionNTopJetSelection);

    RegisterHistCollection( new SemileptonicselectionHists("histoTriggerSelection") );
    RegisterHistCollection( new SemileptonicselectionHists("histoNPrimaryVertexSelection") );
    RegisterHistCollection( new SemileptonicselectionHists("histoNElectronSelection") );
    RegisterHistCollection( new SemileptonicselectionHists("histoNMuonSelection") );
    RegisterHistCollection( new SemileptonicselectionHists("histoNJetSelection") );
    RegisterHistCollection( new SemileptonicselectionHists("histoNTopJetSelection") );
    */
    
    
    
    
    Selection* nleptbtags = new Selection("nleptbtags");

    //Add again
    nleptbtags->addSelectionModule(new NMuonBTagSelection2(1,int_infinity(),e_CSVM,30.,2.4)); // at least one b-jet in the muon hemisphere with pt>30GeV and eta<2.5

    RegisterSelection(nleptbtags);

    //Add again
    Selection* probesele = new Selection("probesele");

    //if(m_ValidationType == "toptagger"){
      
    //Add again
    probesele->addSelectionModule(new NAntiMuonSubBTagSelection2(1,1,e_CSVM,200.,2.4)); // one b-tagged subjets of topjet in the muon anti-hemisphere with pt>150GeV and eta<2.5
      
    //}

    //if(m_ValidationType == "btagging"){

    //Do not add -> for b-tagging validation
    //probesele->addSelectionModule(new NAntiMuonHEPTopSelection(1,1,150.,2.5)); // at least one top-tagged jet in the muon anti-hemisphere with pt>150GeV and eta<2.5

    //}

    RegisterSelection(probesele);

    //Add again
    Selection* htcut = new Selection("htcut");

    htcut->addSelectionModule(new HTlepCut(150.));
 
    RegisterSelection(htcut);

    //Add again
    Selection* etmiss = new Selection("etmiss");

    RegisterSelection(etmiss);

    etmiss->addSelectionModule(new METCut(20.));

    //new
    Selection* njets = new Selection("njets");

    RegisterSelection(njets);
    
    //njets->addSelectionModule(new NHadTopJetSelection(1,1,200.,2.4,PI/2));//int_infinity()
    njets->addSelectionModule(new NHadTopJetSelection2(1,int_infinity(),200.,2.4,PI/2));
    
    //new
    //Selection* masswindow = new Selection("masswindow");

//     RegisterSelection(masswindow);
//     
//     masswindow->addSelectionModule(/*new NHadTopJetSelection(1,1,150.,2.5,2*PI/3)*/new NAndInvMassMuAK5BtagLeptSelection(1,int_infinity(),80.,150.,150.,e_CSVM,2.4,PI/2));//
//     
    
    //NAndInvMassMuAK5BtagLeptSelection(int min_nparticle, int max_nparticle,  double min_mass, double max_mass, double ptmin, E_BtagType type, double etamax, double deltaphi)
    
    // hep top tag & mass cut combinations
    Selection* heptoptag_masscut = new Selection("heptoptag_masscut");
    RegisterSelection(heptoptag_masscut);
    heptoptag_masscut->addSelectionModule(new heptoptag_masscut_Selection());//
    
//     Selection* NOheptoptag_masscut = new Selection("NOheptoptag_masscut");
//     RegisterSelection(NOheptoptag_masscut);
//     NOheptoptag_masscut->addSelectionModule(new NOheptoptag_masscut_Selection());//
    
    Selection* heptoptag_NOmasscut = new Selection("heptoptag_NOmasscut");
    RegisterSelection(heptoptag_NOmasscut);
    heptoptag_NOmasscut->addSelectionModule(new heptoptag_NOmasscut_Selection());//
    
    Selection* pt200 = new Selection("pt200");
    RegisterSelection(pt200);
    pt200->addSelectionModule(new NHadTopJetSelection2(1,1,200.,2.4,PI/2));// 
    
    Selection* pt250 = new Selection("pt250");
    RegisterSelection(pt250);
    pt250->addSelectionModule(new NHadTopJetSelection2(1,1,250.,2.4,PI/2));// 
    
    Selection* pt300 = new Selection("pt300");
    RegisterSelection(pt300);
    pt300->addSelectionModule(new NHadTopJetSelection2(1,1,300.,2.4,PI/2));// 
    
    Selection* pt350 = new Selection("pt350");
    RegisterSelection(pt350);
    pt350->addSelectionModule(new NHadTopJetSelection2(1,1,350.,2.4,PI/2));// 
    
    Selection* pt400 = new Selection("pt400");
    RegisterSelection(pt400);
    pt400->addSelectionModule(new NHadTopJetSelection2(1,1,400.,2.4,PI/2));// 
    
    RegisterHistCollection( new SemileptonicselectionHists("nocutshists") );
    //RegisterHistCollection( new SemileptonicPreselectionHists("triggerhists") );
    //RegisterHistCollection( new SemileptonicPreselectionHists("preselectionhists") );
    RegisterHistCollection( new SemileptonicselectionHists("nleptbtagshists") );
    RegisterHistCollection( new SemileptonicselectionHists("probeselehists") );
    RegisterHistCollection( new SemileptonicselectionHists("htcuthists") );
    RegisterHistCollection( new SemileptonicselectionHists("etmisshists") );
    RegisterHistCollection( new SemileptonicselectionHists("njetshists") );
    RegisterHistCollection( new SemileptonicselectionHists("masswindowhists") );
    
    RegisterHistCollection( new SemileptonicselectionHists("heptoptag_masscut_hists") );
    RegisterHistCollection( new SemileptonicselectionHists("heptoptag_masscut_nsub_hists") );
    RegisterHistCollection( new SemileptonicselectionHists("NOheptoptag_NOmasscut_hists") );
    //no pt rew
    RegisterHistCollection( new SemileptonicselectionHists("heptoptag_masscut_hists_notpr") );
    RegisterHistCollection( new SemileptonicselectionHists("NOheptoptag_NOmasscut_hists_notpr") );
    
    RegisterHistCollection( new SemileptonicselectionHists("NOheptoptag_masscut_hists") );
    RegisterHistCollection( new SemileptonicselectionHists("heptoptag_NOmasscut_hists") );
    RegisterHistCollection( new SemileptonicselectionHists("heptoptag_NOmasscut__NOheptoptag_masscut_hists") );

    RegisterHistCollection( new SemileptonicselectionHists("pt200hists") );
    RegisterHistCollection( new SemileptonicselectionHists("pt250hists") );
    RegisterHistCollection( new SemileptonicselectionHists("pt300hists") );
    RegisterHistCollection( new SemileptonicselectionHists("pt350hists") );
    RegisterHistCollection( new SemileptonicselectionHists("pt400hists") );
    RegisterHistCollection( new SemileptonicselectionHists("ptlowhists") );
    RegisterHistCollection( new SemileptonicselectionHists("pt300histshtt") );
    RegisterHistCollection( new SemileptonicselectionHists("pt400histshtt") );
    
    RegisterHistCollection( new SemileptonicselectionHists("before_tpr_hists") );
    RegisterHistCollection( new SemileptonicselectionHists("after_tpr_hists") );
    
//     RegisterHistCollection( new SemileptonicselectionHists("mcmatch_NOhtt") );
//     RegisterHistCollection( new SemileptonicselectionHists("NOmcmatch_NOhtt") );
//     RegisterHistCollection( new SemileptonicselectionHists("mcmatch_htt") );
//     RegisterHistCollection( new SemileptonicselectionHists("NOmcmatch_htt") );
//     
//     RegisterHistCollection( new SemileptonicselectionHists("mcmatch_NOhtt_pt") );
//     RegisterHistCollection( new SemileptonicselectionHists("NOmcmatch_NOhtt_pt") );
//     RegisterHistCollection( new SemileptonicselectionHists("mcmatch_htt_pt") );
//     RegisterHistCollection( new SemileptonicselectionHists("NOmcmatch_htt_pt") );
    
    RegisterHistCollection( new SemileptonicselectionHists("eta0p5") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0") );
    RegisterHistCollection( new SemileptonicselectionHists("eta2p4") );
    RegisterHistCollection( new SemileptonicselectionHists("eta0p5to1p0") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0to2p4") );
    
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0_400") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0to2p4_400") );
    
    RegisterHistCollection( new SemileptonicselectionHists("eta0p5_HTT") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0_HTT") );
    RegisterHistCollection( new SemileptonicselectionHists("eta2p4_HTT") );
    RegisterHistCollection( new SemileptonicselectionHists("eta0p5to1p0_HTT") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0to2p4_HTT") );
    
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0_HTT_nsub") );
    RegisterHistCollection( new SemileptonicselectionHists("eta1p0to2p4_HTT_nsub") );
      
    RegisterHistCollection( new BTagEffHistsHadTop("BTagEff") );
    Book( TH1D( "LeptToppt_2", ";Pt leptonic top (GeV);Events", 25, 0, 1000));
     // important: initialise histogram collections after their definition
    InitHistos();

    return;
}

void SemileptonicHepTopTagValSelCycle::EndInputData( const SInputData& id ) throw( SError )
{
    AnalysisCycle::EndInputData( id );
    /*TFile * f = new TFile("topptweightcrosscheck.root","RECREATE");
    TopPtWeightHisto->Write();
    TopPtFullWeightHisto->Write();
    TopWeightVsPtHisto->Write();
    TopWeightVsGenPtHisto->Write();
    EventCount->Write();
    f->Close();
    delete f;*/
    return;
}

void SemileptonicHepTopTagValSelCycle::BeginInputFile( const SInputData& id ) throw( SError )
{
    // Connect all variables from the Ntuple file with the ones needed for the analysis
    // The variables are commonly stored in the BaseCycleContaincer

    // important: call to base function to connect all variables to Ntuples from the input tree
    AnalysisCycle::BeginInputFile( id );

    return;
}

void SemileptonicHepTopTagValSelCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError )
{

    // this is the most important part: here the full analysis happens
    // user should implement selections, filling of histograms and results

    // first step: call Execute event of base class to perform basic consistency checks
    // also, the good-run selection is performed there and the calculator is reset

    BaseHists* Hists_before_tpr = GetHistCollection("before_tpr_hists");
    BaseHists* Hists_after_tpr = GetHistCollection("after_tpr_hists");
    
    AnalysisCycle::ExecuteEvent( id, weight);
    EventCalc* calc = EventCalc::Instance();
    BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
    bool IsRealData = calc->IsRealData();
    if (!IsRealData)
    {
      if (id.GetVersion()=="TTbarsemi_powheg")
      {
	TTbarGen* Decay = calc->GetTTbarGen();
	if (!(Decay->DecayChannel()==TTbarGen::e_muhad))//semi
	{
	  throw SError( SError::SkipEvent );
	  return;
	}
      }
      
      if (id.GetVersion()=="TTbarlept_powheg")
      {
	TTbarGen* Decay = calc->GetTTbarGen();
	if (Decay->DecayChannel()==TTbarGen::e_muhad)//not semi
	{
	  throw SError( SError::SkipEvent );
	  return;
	}
      }
      if (id.GetVersion()=="TTbarlept_mcatnlo")
      {
	int islept=0;
	int isq=0;
	std::vector<GenParticle>* genparticles = calc->GetGenParticles();
	for(unsigned int i=0; i<genparticles->size();i++)
	{
	  GenParticle genp=genparticles->at(i);
	  if (abs(genp.pdgId())<=4) isq++;
	  if (abs(genp.pdgId())<=16 && abs(genp.pdgId())>=11) islept++;
	}
	if ((islept>0 && isq>0)) {throw SError( SError::SkipEvent ); return;}
	
	
	std::vector<float> genweights =  bcc->genInfo->weights();
	for(unsigned int i=0; i< genweights.size(); ++i) {
	  //double segno=1.0;
	  //if  (genweights[i]<0) segno=-1.0;
	  calc -> ProduceWeight(1.0/genweights[i]);
	}
      }
      if (id.GetVersion()=="TTbarsemi_mcatnlo")
      {
	int islept=0;
	int isq=0;
	std::vector<GenParticle>* genparticles = calc->GetGenParticles();
	for(unsigned int i=0; i<genparticles->size();i++)
	{
	  GenParticle genp=genparticles->at(i);
	  if (abs(genp.pdgId())<=4) isq++;
	  if (abs(genp.pdgId())<=16 && abs(genp.pdgId())>=11) islept++;
	}
	if (!(islept>0 && isq>0)) {throw SError( SError::SkipEvent ); return;}
	
	
	std::vector<float> genweights =  bcc->genInfo->weights();
	for(unsigned int i=0; i< genweights.size(); ++i) {
	  //double segno=1.0;
	  //if  (genweights[i]<0) segno=-1.0;
	  calc -> ProduceWeight(1.0/genweights[i]);
	}
      }
    }
/*   int islept=0;
   int isq=0;
   std::vector<GenParticle>* genparticles = calc->GetGenParticles();
   for(unsigned int i=0; i<genparticles->size();i++)
   {
     GenParticle genp=genparticles->at(i);
     if (abs(genp.pdgId())<=4) isq++;
     if (abs(genp.pdgId())<=16 && abs(genp.pdgId())>=11) islept++;
   }
   if (!(islept>0 && isq>0)) {throw SError( SError::SkipEvent ); return;}
     
    
    std::vector<float> genweights =  bcc->genInfo->weights();
    for(unsigned int i=0; i< genweights.size(); ++i) {
      //double segno=1.0;
      //if  (genweights[i]<0) segno=-1.0;
      calc -> ProduceWeight(1.0/genweights[i]);
    }

  */  
//     for(unsigned int i=0; i<bcc->genparticles->size(); ++i)
//     {/scratch/hh/dust/naf/cms/user/imarches/gitSFrame/SemileptPre/SemileptonicPreselectionCycle
//       if (abs(bcc->genparticles->at(i).pdgId())<6)
//       std::cout<<bcc->genparticles->at(i).pdgId()<<std::endl;
//     }
   // cout<<std::endl;

      Cleaner cleaner;
/*	
    std::vector<Jet> uncleaned_jets;
    for(unsigned int i=0; i<bcc->jets->size(); ++i) {
        uncleaned_jets.push_back(bcc->jets->at(i));
    }
    MET uncleaned_met = *bcc->met;
  */
   //if(bcc->muons) cleaner.MuonCleaner(26,2.1);
   if(bcc->muons) cleaner.MuonCleaner(45,2.1);
   if(bcc->electrons) cleaner.ElectronCleaner(35,2.5);

   if (bcc->muons->size()==0) throw SError( SError::SkipEvent );
   
/*
    if(bcc->muons) cleaner.MuonCleaner_noIso(45,2.1);
    if(bcc->electrons) cleaner.ElectronCleaner_noIso(35,2.5);
    if(bcc->jets) cleaner.JetLeptonSubtractor(m_corrector,false);
    if(bcc->toptagjets) cleaner.TopJetLeptonSubtractor(m_correctorTopJet,false,1.5);
  */  
    
    double weight1=calc->GetWeight();
    //std::cout<<"weight1: "<<calc->GetWeight()<<std::endl;
       // cout<<calc->GetWeight()<<endl;
    if(m_bsf!=NULL) {
      calc->ProduceWeight(m_bsf->GetScaleWeight());
    }//else{cout<<"what";}
    //double weight2=calc->GetWeight();
    //Hists_before_tpr->Fill();
    //std::cout<<"weight2: "<<calc->GetWeight()<<std::endl;
    
/*    if((!IsRealData) && (id.GetVersion()=="TTbarlept" || id.GetVersion()=="TTbarhad" || id.GetVersion()=="TTbarsemi")) {
      calc->ProduceWeight(m_tpr->GetScaleWeight());
    }*/
    
    //double weight3=calc->GetWeight();
    //Hists_after_tpr->Fill();

    //std::cout<<"weight3: "<<calc->GetWeight()<<std::endl<<std::endl;
    //std::cout<<"weight from ratio: "<<weight3/weight2<<std::endl;
    /*TTbarGen* Decay = calc->GetTTbarGen();
    GenParticle topgen=Decay->Top();
    GenParticle antitopgen=Decay->Antitop();
    TopPtWeightHisto->Fill(m_bsf->GetScaleWeight());
    TopPtFullWeightHisto->Fill(calc->GetWeight());
    int tprindex = findTheHighestPtGoodTopJet(bcc);
    if (tprindex>-1) TopWeightVsPtHisto->Fill(bcc->toptagjets->at(tprindex).pt(),m_bsf->GetScaleWeight());
    TopWeightVsGenPtHisto->Fill(topgen.pt(),m_bsf->GetScaleWeight());
    TopWeightVsGenPtHisto->Fill(antitopgen.pt(),m_bsf->GetScaleWeight());
    EventCount->Fill(0.1,weight2);
    EventCount->Fill(1.1,weight3);*/

    //std::cout<<std::endl;
    //static Selection* trigger = GetSelection("trigger");
    //static Selection* preselectionNPrimaryVertexSelection = GetSelection("preselectionNPrimaryVertexSelection");
    //static Selection* preselectionNElectronSelection = GetSelection("preselectionNElectronSelection");
    //static Selection* preselectionNMuonSelection = GetSelection("preselectionNMuonSelection");
    //static Selection* preselectionNJetSelection = GetSelection("preselectionNJetSelection");//at least two jets with pt>30GeV and eta<2.5
    //static Selection* preselectionNTopJetSelection = GetSelection("preselectionNTopJetSelection");//at least one jet with pt>150GeV and eta<2.5
    //static Selection* preselection = GetSelection("preselection");
    
    
    static Selection* nleptbtags = GetSelection("nleptbtags");
    static Selection* probesele = GetSelection("probesele");
    static Selection* htcut = GetSelection("htcut");
    static Selection* etmiss = GetSelection("etmiss");
    static Selection* njets = GetSelection("njets");
    //static Selection* masswindow = GetSelection("masswindow");
    
    static Selection* heptoptag_masscut = GetSelection("heptoptag_masscut");
//     static Selection* NOheptoptag_masscut = GetSelection("NOheptoptag_masscut");
    static Selection* heptoptag_NOmasscut = GetSelection("heptoptag_NOmasscut");
    
    static Selection* pt200 = GetSelection("pt200");
    static Selection* pt250 = GetSelection("pt250");
    static Selection* pt300 = GetSelection("pt300");
    static Selection* pt350 = GetSelection("pt350");
    static Selection* pt400 = GetSelection("pt400");

    //BaseHists* HistsTriggerSelection = GetHistCollection("histoTriggerSelection");
    //BaseHists* HistsNPrimaryVertexSelection = GetHistCollection("histoNPrimaryVertexSelection");
    //BaseHists* HistsNElectronSelection = GetHistCollection("histoNElectronSelection");
    //BaseHists* HistsNMuonSelection = GetHistCollection("histoNMuonSelection");
    //BaseHists* HistsNJetSelection = GetHistCollection("histoNJetSelection");
    //BaseHists* HistsNTopJetSelection = GetHistCollection("histoNTopJetSelection");
    
    BaseHists* Histsnocuts = GetHistCollection("nocutshists");
    //BaseHists* Histstrigger = GetHistCollection("triggerhists");
    //BaseHists* Histspreselection = GetHistCollection("preselectionhists");
    BaseHists* Histsnleptbtags = GetHistCollection("nleptbtagshists");
    BaseHists* Histsprobesele = GetHistCollection("probeselehists");
    BaseHists* Histshtcut = GetHistCollection("htcuthists");
    BaseHists* Histsetmiss = GetHistCollection("etmisshists");
    BaseHists* Histsnjets = GetHistCollection("njetshists");
    BaseHists* Histsmasswindow = GetHistCollection("masswindowhists");
    
    BaseHists* Hists_heptoptag_masscut = GetHistCollection("heptoptag_masscut_hists");
    BaseHists* Hists_heptoptag_masscut_nsub = GetHistCollection("heptoptag_masscut_nsub_hists");
    BaseHists* Hists_NOheptoptag_NOmasscut = GetHistCollection("NOheptoptag_NOmasscut_hists");
    BaseHists* Hists_heptoptag_masscut_notpr = GetHistCollection("heptoptag_masscut_hists_notpr");
    BaseHists* Hists_NOheptoptag_NOmasscut_notpr = GetHistCollection("NOheptoptag_NOmasscut_hists_notpr");
    BaseHists* Hists_NOheptoptag_masscut = GetHistCollection("NOheptoptag_masscut_hists");
    BaseHists* Hists_heptoptag_NOmasscut = GetHistCollection("heptoptag_NOmasscut_hists");
    BaseHists* Hists_heptoptag_NOmasscut__NOheptoptag_masscut = GetHistCollection("heptoptag_NOmasscut__NOheptoptag_masscut_hists");
    
    BaseHists* Histspt200 = GetHistCollection("pt200hists");
    BaseHists* Histspt250 = GetHistCollection("pt250hists");
    BaseHists* Histspt300 = GetHistCollection("pt300hists");
    BaseHists* Histspt350 = GetHistCollection("pt350hists");
    BaseHists* Histspt400 = GetHistCollection("pt400hists");
    BaseHists* Histsptlow = GetHistCollection("ptlowhists");
    BaseHists* Histspt300htt = GetHistCollection("pt300histshtt");
    BaseHists* Histspt400htt = GetHistCollection("pt400histshtt");  
    
//     BaseHists* Hists_mcmatch_NOhtt = GetHistCollection("mcmatch_NOhtt");
//     BaseHists* Hists_NOmcmatch_NOhtt = GetHistCollection("NOmcmatch_NOhtt");
//     BaseHists* Hists_mcmatch_htt = GetHistCollection("mcmatch_htt");
//     BaseHists* Hists_NOmcmatch_htt = GetHistCollection("NOmcmatch_htt");
//     
//     BaseHists* Hists_mcmatch_NOhtt_pt = GetHistCollection("mcmatch_NOhtt_pt");
//     BaseHists* Hists_NOmcmatch_NOhtt_pt = GetHistCollection("NOmcmatch_NOhtt_pt");
//     BaseHists* Hists_mcmatch_htt_pt = GetHistCollection("mcmatch_htt_pt");
//     BaseHists* Hists_NOmcmatch_htt_pt = GetHistCollection("NOmcmatch_htt_pt");
    
    BaseHists* Hists_eta0p5 = GetHistCollection("eta0p5");
    BaseHists* Hists_eta1p0 = GetHistCollection("eta1p0");
    BaseHists* Hists_eta2p4 = GetHistCollection("eta2p4");
    BaseHists* Hists_eta0p5to1p0 = GetHistCollection("eta0p5to1p0");
    BaseHists* Hists_eta1p0to2p4 = GetHistCollection("eta1p0to2p4");
    
    BaseHists* Hists_eta1p0_400 = GetHistCollection("eta1p0_400");
    BaseHists* Hists_eta1p0to2p4_400 = GetHistCollection("eta1p0to2p4_400");
    
    BaseHists* Hists_eta0p5_HTT = GetHistCollection("eta0p5_HTT");
    BaseHists* Hists_eta1p0_HTT = GetHistCollection("eta1p0_HTT");
    BaseHists* Hists_eta2p4_HTT = GetHistCollection("eta2p4_HTT");
    BaseHists* Hists_eta0p5to1p0_HTT = GetHistCollection("eta0p5to1p0_HTT");
    BaseHists* Hists_eta1p0to2p4_HTT = GetHistCollection("eta1p0to2p4_HTT");
    
    BaseHists* Hists_eta1p0_HTT_nsub = GetHistCollection("eta1p0_HTT_nsub");
    BaseHists* Hists_eta1p0to2p4_HTT_nsub = GetHistCollection("eta1p0to2p4_HTT_nsub");
    
    BaseHists* specialSFeffi = GetHistCollection("BTagEff");

   Histsnocuts->Fill();

    //if(!trigger->passSelection()) throw SError( SError::SkipEvent );

    //if(!preselection->passSelection()) throw SError( SError::SkipEvent );
    
    /*
    if(trigger->passSelection()){HistsTriggerSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNPrimaryVertexSelection->passSelection()){HistsNPrimaryVertexSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNElectronSelection->passSelection()){HistsNElectronSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNMuonSelection->passSelection()){HistsNMuonSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNJetSelection->passSelection()){HistsNJetSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNTopJetSelection->passSelection()){HistsNTopJetSelection->Fill();}
    else{throw SError( SError::SkipEvent );}
    */
  
  
    /*if(trigger->passSelection())  Histstrigger->Fill();
    else throw SError( SError::SkipEvent );

    if(preselection->passSelection())  Histspreselection->Fill();
    else throw SError( SError::SkipEvent );*/

    if(nleptbtags->passSelection())  Histsnleptbtags->Fill();
    else throw SError( SError::SkipEvent );

    if(njets->passSelection())  Histsnjets->Fill();
    else throw SError( SError::SkipEvent );
    
    
    specialSFeffi->Fill();
    
    if(probesele->passSelection())  Histsprobesele->Fill();
    else throw SError( SError::SkipEvent );

    Hists_after_tpr->Fill();
    
  /*  if(htcut->passSelection())  Histshtcut->Fill();
    else throw SError( SError::SkipEvent );

    if(etmiss->passSelection())  Histsetmiss->Fill();
    else throw SError( SError::SkipEvent );*/
    
   
    
   // Hists_before_tpr->Fill();
    //std::cout<<"weight2: "<<calc->GetWeight()<<std::endl;
   // if((!IsRealData) && (id.GetVersion()=="TTbarlept" || id.GetVersion()=="TTbarhad" || id.GetVersion()=="TTbarsemi")) {
  //    calc->ProduceWeight(m_tpr->GetScaleWeight());
  //  }
    //double weight3=calc->GetWeight();
  //  Hists_after_tpr->Fill();
    
    //we lose too much signal with this cut + data/mc gets around 80% (why?)
//     if(masswindow->passSelection())  Histsmasswindow->Fill();
    //else throw SError( SError::SkipEvent );

    

 
    
 ////////////////////////pt rewe   
     double rewe_ptbins[] = {1.6643064190110375, 1.1291049475519348, 1.0202523726223109, 1.0100544303577483, 0.96507556827465524, 0.91385700488061128, 0.88075947054973602, 0.87399592611677701, 0.83256822284802456, 0.71532886924548367, 0.82345388810441489, 0.63650558325110151, 0.76690298621827901, 0.70367232819173031, 0.65992411119525607, 0.76305059550410648, 0.49017053899100721, 1.2075539534561064, 1.7131374083819584, 0.37814339424720761, 0.97079697617297389, 0.0, 0.0, 0.0, 0.0};
     
     //mcatnlo{1.1660494527326521, 1.070128181860341, 1.0247680322312291, 1.0554103138926527, 1.0192481232505697, 0.9762002666330184, 0.96689007198830235, 0.98032498922695555, 0.93117931091101147, 0.78522013019139691, 0.9946259752976977, 0.78040738266364729, 0.94167779045990063, 1.0142923425938801, 0.86359258680261375, 1.0965345068093457, 0.74244864534091659, 1.9549446306018676, 5.131980725161351, 0.8415218908576988, 0.96923087912985528, 0.0, 0.0, 0.0, 0.0};
     
     //powheg{1.0540981229205111, 1.0491537443616747, 1.0516120896399024, 1.0217328894038467, 0.99189206215528014, 0.95949138671721812, 0.92334598280238067, 0.93950497463458182, 0.89345016219300044, 0.79158447702007051, 0.94037987693367564, 0.72812980556564955, 0.90041741676956544, 0.79737425523846928, 0.63784987669244853, 1.175229826623833, 0.50198663930373366, 1.1754766725085191, 2.4547707895378794, 0.35382097194133955, 1.2069385513588105, 0.0, 0.0, 0.0, 0.0};
     
     //madgraph{1.6643064190110375, 1.1291049475519348, 1.0202523726223109, 1.0100544303577483, 0.96507556827465524, 0.91385700488061128, 0.88075947054973602, 0.87399592611677701, 0.83256822284802456, 0.71532886924548367, 0.82345388810441489, 0.63650558325110151, 0.76690298621827901, 0.70367232819173031, 0.65992411119525607, 0.76305059550410648, 0.49017053899100721, 1.2075539534561064, 1.7131374083819584, 0.37814339424720761, 0.97079697617297389, 0.0, 0.0, 0.0, 0.0};
 
//      {1.4612986856185965, 0.98068541128450237, 1.0246260208591065, 1.022516647893609, 0.92472987208576907, 0.8825980121166922, 0.87091184592860016, 0.87232123434987374, 0.78907802576406649, 0.68818178005381037, 0.76628084218446146, 0.59837986427987933, 0.66694143327184197, 0.76758494988372972, 0.82094688446830033, 0.53676653945801234, 0.42985275217439595, 1.068483205365754, 0.87261746150587705, 0.6046579518718288, 0.54506516740293542, 0.0, 1.2466886288731063, 0.0, 0.0};
     //{1.4612986856185965, 0.98068541128450237, 1.0227855320044323, 1.0209141604003322, 0.9137700831574892, 0.8825980121166922, 0.87091184592860016, 0.87178591259501259, 0.78901763683150417, 0.68806515195398554, 0.76627981008939494, 0.59802243719012416, 0.66469342764345896, 0.7672362655458288, 0.82070692705205972, 0.53676653945801234, 0.42985275217439595, 1.068483205365754, 0.87261746150587705, 0.6046579518718288, 0.54506516740293542, 0.0, 1.2466886288731063, 0.0, 0.0};
     //{1.4537274666667401, 0.93262923875901094, 0.96695518414079018, 1.0313614664987996, 0.93139420044909926, 0.88160504805702677, 0.87843116976879987, 0.87613185142751571, 0.78153236086122457, 0.69375217644344722, 0.77637250552595261, 0.58494476184048805, 0.67956639050826761, 0.70860459255671648, 0.88160165788765343, 0.5719136267870214, 0.51243231615553908, 0.94469496659154661, 0.83192470980294886, 0.35494571199080843, 0.54538350226340893, 0.0, 1.5067911654681068, 0.0, 0.0};
     //{1.1015192493955237, 1.072969626499942, 1.059773713264814, 1.0443808069843499, 0.97559435187234156, 0.92037396322447862, 0.90106385676970291, 0.89780994470266151, 0.82138438081222853, 0.71448665074196815, 0.80760760996403691, 0.60732070468100741, 0.71063064177692392, 0.79835833468750228, 0.94408505738812731, 0.55833370922937819, 0.47896670100389144, 1.1010209709172742, 0.77494621322844492, 0.66090989990785964, 0.54856125704616832, 0.0, 0.93759753206857099, 0.0, 0.0};
     //{1.1034406589456662, 1.0781626530903581, 1.0688606064573538, 1.0436203959501331, 0.96563662527836047, 0.9249614422791359, 0.90480008616270435, 0.89334079715800929, 0.83294143165262247, 0.72836786616574478, 0.81339848853460672, 0.62614015936025547, 0.71133590319815532, 0.80890967510044332, 0.96281532775741197, 0.57178637129701004, 0.47896670100389144, 1.1010209709172742, 0.77494621322844492, 0.67510429119721682, 0.54856125704616832, 0.0, 0.9375975320685711, 0.0, 0.0};
    
  //  double rewe_ptbins[] = {1.2694419764470888, 0.96154145627548793, 1.101005986463361, 1.1506693685250007, 1.0547730804191993, 1.0111940743992489, 1.0251036013668913, 1.0415090426670981, 0.99020169622267318, 0.87418675528746537, 1.0679539025912632, 0.79970773095293601, 0.94814411030727652, 1.2759271724208803, 1.2869187480757904, 0.82078797168570528, 0.85970481397191489, 1.5452920051391881, 2.7163888905709954, 1.3230664479537853, 0.66003292184312912, 0.0, 0.97169949641664699, 0.0, 0.0};


    int goodleptjetindex=-1;
    float maxleptjetpt=-1;
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

    if (!IsRealData)
    {
      LorentzVector lepttop(0,0,0,0); 
      lepttop+=bcc->jets->at(goodleptjetindex).v4();
      lepttop+=bcc->muons->at(0).v4();
      lepttop+=bcc->met->v4();
      int leptbin=Hist("LeptToppt_2" )->Fill(lepttop.Pt());
      if (leptbin>-1) calc->ProduceWeight(rewe_ptbins[leptbin-1]);
    }

  }
    
////////////////end pt rewe    
     //if(pt200->passSelection()) Histspt200->Fill(); else throw SError( SError::SkipEvent );
 
    int nparticle=0;
    for(unsigned int i=0; i<bcc->toptagjets->size(); ++i) {
      if(bcc->toptagjets->at(i).pt()<400 && fabs(bcc->toptagjets->at(i).eta())<2.4 && bcc->toptagjets->at(i).deltaR(bcc->muons->at(0))>PI/2) nparticle++;
    }   


    int indexjet=findTheHighestPtGoodTopJet(bcc);
    
    //mc matching
    bool isMCMatched=false;
//     if(!IsRealData)
//     {
//       //Filling generator-level information for semi-leptonic ttbar events
//       TTbarGen* Decay = calc->GetTTbarGen();
// 
//       if(indexjet>-1)
//       {
// 	//cout<<Decay->DecayChannel()<<endl;
// 	/*cout<<"top "<<bcc->toptagjets->at(indexjet).deltaR(Decay->TopHad())<<endl;
// 	cout<<"b "<<bcc->toptagjets->at(indexjet).deltaR(Decay->BHad())<<endl;
// 	cout<<"w "<<bcc->toptagjets->at(indexjet).deltaR(Decay->WHad())<<endl;
// 	cout<<"q1 "<<bcc->toptagjets->at(indexjet).deltaR(Decay->Q1())<<endl;
// 	cout<<"q2 "<<bcc->toptagjets->at(indexjet).deltaR(Decay->Q2())<<endl;
// 	cout<<"\n\n\n\n"<<endl;*/
// 	if(bcc->toptagjets->at(indexjet).deltaR(Decay->TopHad())<1.5 && bcc->toptagjets->at(indexjet).deltaR(Decay->BHad())<1.5 && bcc->toptagjets->at(indexjet).deltaR(Decay->WHad())<1.5 && bcc->toptagjets->at(indexjet).deltaR(Decay->Q1())<1.5 && bcc->toptagjets->at(indexjet).deltaR(Decay->Q2())<1.5)
// 	{
// 	  isMCMatched=true;
// 	}
//       }
//     }
//     if (isMCMatched)
//     {
//       Hists_mcmatch_NOhtt->Fill();
//       if (pt200->passSelection() && (nparticle>0)) Hists_mcmatch_NOhtt_pt->Fill();
//     }
//     else
//     {
//       Hists_NOmcmatch_NOhtt->Fill();
//       if (pt200->passSelection() && (nparticle>0)) Hists_NOmcmatch_NOhtt_pt->Fill();
//     }
//     
//     if (isMCMatched && heptoptag_masscut->passSelection()) Hists_mcmatch_htt->Fill();
//     if (isMCMatched && heptoptag_masscut->passSelection() && pt300->passSelection()) Hists_mcmatch_htt_pt->Fill();
//     if (!isMCMatched && heptoptag_masscut->passSelection()) Hists_NOmcmatch_htt->Fill();
//     if (!isMCMatched && heptoptag_masscut->passSelection() && pt300->passSelection()) Hists_NOmcmatch_htt_pt->Fill();
    
    //next cuts are in parallel (= no skip event if not passed)
    
    //no hep top tag no mass cut
    Hists_NOheptoptag_NOmasscut_notpr->Fill();
    //normal hep top tagger with mass cut
    if(heptoptag_masscut->passSelection())  Hists_heptoptag_masscut_notpr->Fill();
    
    //apply pt reweight
//     if((!IsRealData) && (id.GetVersion()=="TTbarlept" || id.GetVersion()=="TTbarhad" || id.GetVersion()=="TTbarsemi"
//       || id.GetVersion()=="TTJets_matchingdown"
//       || id.GetVersion()=="TTJets_matchingup"
//       || id.GetVersion()=="TTJets_scaledown"
//       || id.GetVersion()=="TTJets_scaleup"
//     )) {
//       calc->ProduceWeight(m_tpr->GetScaleWeight());
//     }
//   
      //pt top cuts

    
    if(pt250->passSelection())  Histspt250->Fill();

    if(pt300->passSelection())  Histspt300->Fill(); //else throw SError( SError::SkipEvent );
    
    if(pt350->passSelection())  Histspt350->Fill();
	
    if(pt400->passSelection() /*&& heptoptag_masscut->passSelection()*/)
    {
      Histspt400->Fill();
      if(indexjet>-1)
      {
	float topeta=fabs(bcc->toptagjets->at(indexjet).eta());
	if(topeta<1.0){Hists_eta1p0_400->Fill();}
	if(topeta>1.0 && topeta<2.4){Hists_eta1p0to2p4_400->Fill();}
      }
    }
    
    if(nparticle>0 && heptoptag_masscut->passSelection())  Histsptlow->Fill();
  
  
  
     //no hep top tag no mass cut
    Hists_NOheptoptag_NOmasscut->Fill();
    if(indexjet>-1)
    {
      float topeta=fabs(bcc->toptagjets->at(indexjet).eta());
      if(topeta<0.5){Hists_eta0p5->Fill();}
      if(topeta<1.0){Hists_eta1p0->Fill();}
      if(topeta<2.4){Hists_eta2p4->Fill();}
      if(topeta>0.5 && topeta<1.0){Hists_eta0p5to1p0->Fill();}
      if(topeta>1.0 && topeta<2.4){Hists_eta1p0to2p4->Fill();}
    }
    //normal hep top tagger with mass cut
    if(heptoptag_masscut->passSelection())
    {  
      Hists_heptoptag_masscut->Fill();
      
      if(IsRealData){//cout<<bcc->run<<":"<<bcc->luminosityBlock<<":"<<bcc->event<<endl;
      runs.push_back(bcc->run);
      lumis.push_back(bcc->luminosityBlock);
      evnums.push_back(bcc->event);}
      if(indexjet>-1)
      {
	float topeta=fabs(bcc->toptagjets->at(indexjet).eta());
	if(topeta<0.5){Hists_eta0p5_HTT->Fill();}
	if(topeta<1.0){Hists_eta1p0_HTT->Fill();}
	if(topeta<2.4){Hists_eta2p4_HTT->Fill();}
	if(topeta>0.5 && topeta<1.0){Hists_eta0p5to1p0_HTT->Fill();}
	if(topeta>1.0 && topeta<2.4){Hists_eta1p0to2p4_HTT->Fill();}
      }
      if(indexjet>-1)
      {
        double nsub=getNsub(bcc,indexjet);
	float topeta=fabs(bcc->toptagjets->at(indexjet).eta());
	if(nsub<0.63)
	{
	  Hists_heptoptag_masscut_nsub->Fill();
	  if(topeta<1.0){Hists_eta1p0_HTT_nsub->Fill();}
	  if(topeta>1.0 && topeta<2.4){Hists_eta1p0to2p4_HTT_nsub->Fill();}
	}
      }
    }

    //hep top tagger with no mass cut
    if(heptoptag_NOmasscut->passSelection())
    { 
      Hists_heptoptag_NOmasscut->Fill();
      if(pt300->passSelection())  Histspt300htt->Fill();
      if(pt400->passSelection())  Histspt400htt->Fill(); 
    }
    //mass cut only
//     if(NOheptoptag_masscut->passSelection())  Hists_NOheptoptag_masscut->Fill();

    //normal hep top tagger and mass cut separately
//    if(heptoptag_NOmasscut->passSelection() && NOheptoptag_masscut->passSelection())  Hists_heptoptag_NOmasscut__NOheptoptag_masscut->Fill();
  
    /*
    //fill the uncleaned collections back to bcc to store them in output tree
    bcc->met->set_pt (uncleaned_met.pt());
    bcc->met->set_phi (uncleaned_met.phi());
    bcc->jets->clear();
    for(unsigned int i=0; i<uncleaned_jets.size(); ++i) {
        bcc->jets->push_back(uncleaned_jets.at(i));
    }
    */
    WriteOutputTree();

    return;
}

