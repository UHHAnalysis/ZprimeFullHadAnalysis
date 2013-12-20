#include <iostream>

using namespace std;

// Local include(s):
#include "include/SemileptonicPreselectionCycle.h"
#include "SFrameAnalysis/include/SelectionModules.h"
#include "include/BTagEffHistsTopTag.h"

ClassImp( SemileptonicPreselectionCycle );

SemileptonicPreselectionCycle::SemileptonicPreselectionCycle()
    : AnalysisCycle()
{

    // constructor, declare additional variables that should be
    // obtained from the steering-xml file

    // set the integrated luminosity per bin for the lumi-yield control plots
    SetIntLumiPerBin(25.);
    DeclareProperty( "CSVOperatingPoint", m_CSVOperatingPoint );
    
}

SemileptonicPreselectionCycle::~SemileptonicPreselectionCycle()
{
    // destructor
}

void SemileptonicPreselectionCycle::BeginCycle() throw( SError )
{
    // Start of the job, general set-up and definition of
    // objects are done here

    // Important: first call BeginCycle of base class
    AnalysisCycle::BeginCycle();

    return;

}

void SemileptonicPreselectionCycle::EndCycle() throw( SError )
{
    // clean-up, info messages and final calculations after the analysis


    // call the base cycle class for all standard methods
    // and a summary of the made selections
    AnalysisCycle::EndCycle();

    return;

}

void SemileptonicPreselectionCycle::BeginInputData( const SInputData& id ) throw( SError )
{
    // declaration of histograms and selections

    // Important: first call BeginInputData of base class
    AnalysisCycle::BeginInputData( id );

 
    
    

        
    

    
 
 
 RegisterHistCollection( new BTagEffHistsTopTag("BTagEffJim",atof(m_CSVOperatingPoint.c_str())) );
 
 
 
    
    
    // -------------------- set up the selections ---------------------------

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
    preselectionNTopJetSelection->addSelectionModule(new NTopJetSelection2(1,int_infinity(),150.,2.5));//at least one jet with pt>150GeV and eta<2.5

    RegisterSelection(preselectionNPrimaryVertexSelection);
    RegisterSelection(preselectionNElectronSelection);
    RegisterSelection(preselectionNMuonSelection);
    RegisterSelection(preselectionNJetSelection);
    RegisterSelection(preselectionNTopJetSelection);

//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNoCut") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoTriggerSelection") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNPrimaryVertexSelection") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNElectronSelection") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNMuonSelection") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNJetSelection") );
//     RegisterHistCollection( new SemileptonicPreselectionHists("histoNTopJetSelection") );

    InitHistos();
    return;
}

void SemileptonicPreselectionCycle::EndInputData( const SInputData& id ) throw( SError )
{
    AnalysisCycle::EndInputData( id );
    //delete m_tpr;
    return;
}

void SemileptonicPreselectionCycle::BeginInputFile( const SInputData& id ) throw( SError )
{
    // Connect all variables from the Ntuple file with the ones needed for the analysis
    // The variables are commonly stored in the BaseCycleContaincer

    // important: call to base function to connect all variables to Ntuples from the input tree
    AnalysisCycle::BeginInputFile( id );

    return;
}

void SemileptonicPreselectionCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError )
{
    // this is the most important part: here the full analysis happens
    // user should implement selections, filling of histograms and results

    // first step: call Execute event of base class to perform basic consistency checks
    // also, the good-run selection is performed there and the calculator is reset

    AnalysisCycle::ExecuteEvent( id, weight);

    EventCalc* calc = EventCalc::Instance();
    BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
    
    bool IsRealData = calc->IsRealData();

    BaseHists* BTagEff_Hists = GetHistCollection("BTagEffJim");
    
    
    
    Cleaner cleaner;

    static Selection* trigger = GetSelection("trigger");
    static Selection* preselectionNPrimaryVertexSelection = GetSelection("preselectionNPrimaryVertexSelection");
    static Selection* preselectionNElectronSelection = GetSelection("preselectionNElectronSelection");
    static Selection* preselectionNMuonSelection = GetSelection("preselectionNMuonSelection");
    static Selection* preselectionNJetSelection = GetSelection("preselectionNJetSelection");//at least two jets with pt>30GeV and eta<2.5
    static Selection* preselectionNTopJetSelection = GetSelection("preselectionNTopJetSelection");//at least one jet with pt>150GeV and eta<2.5
    //static Selection* preselection = GetSelection("preselection");
    
    
    //static Selection* nleptbtags = GetSelection("nleptbtags");
    //static Selection* probesele = GetSelection("probesele");
    //static Selection* htcut = GetSelection("htcut");
    //static Selection* etmiss = GetSelection("etmiss");
//     BaseHists* HistsNoCutSelection = GetHistCollection("histoNoCut");
//     BaseHists* HistsTriggerSelection = GetHistCollection("histoTriggerSelection");
//     BaseHists* HistsNPrimaryVertexSelection = GetHistCollection("histoNPrimaryVertexSelection");
//     BaseHists* HistsNElectronSelection = GetHistCollection("histoNElectronSelection");
//     BaseHists* HistsNMuonSelection = GetHistCollection("histoNMuonSelection");
//     BaseHists* HistsNJetSelection = GetHistCollection("histoNJetSelection");
//     BaseHists* HistsNTopJetSelection = GetHistCollection("histoNTopJetSelection");
    
    //BaseHists* Histsnocuts = GetHistCollection("nocutshists");
    //BaseHists* Histstrigger = GetHistCollection("triggerhists");
    //BaseHists* Histspreselection = GetHistCollection("preselectionhists");
    //BaseHists* Histsnleptbtags = GetHistCollection("nleptbtagshists");
    //BaseHists* Histsprobesele = GetHistCollection("probeselehists");
    //BaseHists* Histshtcut = GetHistCollection("htcuthists");
    //BaseHists* Histsetmiss = GetHistCollection("etmisshists");
    
    
    
    //save uncleaned jet collection and MET to be stored in output
    /*std::vector<Jet> uncleaned_jets;
    for(unsigned int i=0; i<bcc->jets->size(); ++i) {
        uncleaned_jets.push_back(bcc->jets->at(i));
    }
    MET uncleaned_met = *bcc->met;*/
    
    //do the cleaning
    if(bcc->muons) cleaner.MuonCleaner(45,2.1);
    //if(bcc->muons) cleaner.MuonCleaner(26,2.1);
    if(bcc->electrons) cleaner.ElectronCleaner(35,2.5);
    /*if(bcc->muons) cleaner.MuonCleaner_noIso(45,2.1);
    if(bcc->electrons) cleaner.ElectronCleaner_noIso(35,2.5);
    if(bcc->jets) cleaner.JetLeptonSubtractor(m_corrector,false);
    if(bcc->topjets) cleaner.TopJetLeptonSubtractor(m_correctorTopJet,false,1.5);*/
    
    //Histsnocuts->Fill();

    //if(!trigger->passSelection()) throw SError( SError::SkipEvent );

    //if(!preselection->passSelection()) throw SError( SError::SkipEvent );
 
 /*
 
 
    std::vector<GenParticle>* genparticles = calc->GetGenParticles();
    int sizegen=genparticles->size();
    for(unsigned int i=0; i<genparticles->size();i++)
    {
      GenParticle genp=genparticles->at(i);
      if (abs(genp.pdgId())==6 || abs(genp.pdgId())==24)
      {
	if (genp.daughter(bcc->genparticles,1)->index()>=sizegen || genp.daughter(bcc->genparticles,2)->index()>=sizegen)
	{
	  //std::cout<<"this is a bad event"<<std::endl;
	  throw SError( SError::SkipEvent );
	  return;
	}
      }
    }
    
    
    
    */
    
//     ((SemileptonicPreselectionHists*)HistsNoCutSelection)->SetIdVersion(id.GetVersion());
//     HistsNoCutSelection->Fill();
    
     if (id.GetVersion()!="TTbarEff" && id.GetVersion()!="QCD15to3000")
     {
    
    if(trigger->passSelection()){/*HistsTriggerSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNPrimaryVertexSelection->passSelection()){/*HistsNPrimaryVertexSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNElectronSelection->passSelection()){/*HistsNElectronSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );} 
    
    if(preselectionNMuonSelection->passSelection()){/*HistsNMuonSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNJetSelection->passSelection()){/*HistsNJetSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );}
    
    if(preselectionNTopJetSelection->passSelection()){/*HistsNTopJetSelection->Fill();*/}
    else{throw SError( SError::SkipEvent );}
  
    if (!IsRealData)
    {
      BTagEff_Hists->Fill();
    }
    }
    /*if(trigger->passSelection())  Histstrigger->Fill();
    else throw SError( SError::SkipEvent );

    if(preselection->passSelection())  Histspreselection->Fill();
    else throw SError( SError::SkipEvent );

    if(nleptbtags->passSelection())  Histsnleptbtags->Fill();
    else throw SError( SError::SkipEvent );

    if(probesele->passSelection())  Histsprobesele->Fill();
    else throw SError( SError::SkipEvent );

    if(htcut->passSelection())  Histshtcut->Fill();
    else throw SError( SError::SkipEvent );

    if(etmiss->passSelection())  Histsetmiss->Fill();
    else throw SError( SError::SkipEvent );
    */
    
    //fill the uncleaned collections back to bcc to store them in output tree
    /*bcc->met->set_pt (uncleaned_met.pt());
    bcc->met->set_phi (uncleaned_met.phi());
    bcc->jets->clear();
    for(unsigned int i=0; i<uncleaned_jets.size(); ++i) {
        bcc->jets->push_back(uncleaned_jets.at(i));
    }*/
     
    WriteOutputTree();

    return;
}

