#include "include/BTagEffHistsTopTag.h"
#include <iostream>

using namespace std;

BTagEffHistsTopTag::BTagEffHistsTopTag(const char* name, float csv) : BaseHists(name)
{
    // named default constructor
    m_CSVOperatingPoint = csv;

}

BTagEffHistsTopTag::~BTagEffHistsTopTag()
{
    // default destructor, does nothing
}


void BTagEffHistsTopTag::Init()
{
    // book all histograms here
    double jetpt_bbins[] = {
        20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800, 1600
    };

    double jetpt_cbins[] = {
        20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 1600
    };

    double jetpt_lbins[] = {
        20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 1600
    };

    // basic jet kinematics
    Book( TH1F( "pt_bJet"," p_{T} b-jets", 17, jetpt_bbins));
    Book( TH1F( "eta_bJet","#eta b-jets", 50,-3,3));
    Book( TH1F( "phi_bJet","#phi b-jets", 50, -PI, PI));

    Book( TH1F( "pt_cJet"," p_{T} c-jets", 14, jetpt_cbins));
    Book( TH1F( "eta_cJet","#eta c-jets", 50,-3,3));
    Book( TH1F( "phi_cJet","#phi c-jets", 50, -PI, PI));

    Book( TH1F( "pt_lJet"," p_{T} l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e1"," p_{T} l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e2"," p_{T} l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e3"," p_{T} l-jets", 16, jetpt_lbins));
    Book( TH1F( "eta_lJet","#eta l-jets", 50,-3,3));
    Book( TH1F( "phi_lJet","#phi l-jets", 50, -PI, PI));

    Book( TH1F( "pt_bJet_bTag"," p_{T} tagged b-jets", 17, jetpt_bbins));
    Book( TH1F( "eta_bJet_bTag","#eta tagged b-jets", 50,-3,3));
    Book( TH1F( "phi_bJet_bTag","#phi tagged b-jets", 50, -PI, PI));

    Book( TH1F( "pt_cJet_bTag"," p_{T} tagged c-jets", 14, jetpt_cbins));
    Book( TH1F( "eta_cJet_bTag","#eta tagged c-jets", 50,-3,3));
    Book( TH1F( "phi_cJet_bTag","#phi tagged c-jets", 50, -PI, PI));

    Book( TH1F( "pt_lJet_bTag"," p_{T} tagged l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e1_bTag"," p_{T} tagged l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e2_bTag"," p_{T} tagged l-jets", 16, jetpt_lbins));
    Book( TH1F( "pt_lJet_e3_bTag"," p_{T} tagged l-jets", 16, jetpt_lbins));
    Book( TH1F( "eta_lJet_bTag","#eta tagged l-jets", 50,-3,3));
    Book( TH1F( "phi_lJet_bTag","#phi tagged l-jets", 50, -PI, PI));
}

void BTagEffHistsTopTag::Fill()
{
    //std::cout<<m_CSVOperatingPoint<<std::endl;
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
    double weight = calc -> GetWeight();


    std::vector<Jet> * jets= bcc->jets;
    for (unsigned int i =0; i<jets->size(); ++i) {
      
      
      double deltaphi=bcc->jets->at(i).deltaR(bcc->muons->at(0));
      if(!((deltaphi<(PI/2))&&(bcc->jets->at(i).pt()>30.)&&(fabs(bcc->jets->at(i).eta())<2.4)))
	continue;
      
      
      Jet jet = jets->at(i);
      int flavour = abs(jet.flavor());
      //float csvcut=0.679;
      bool btag = (jet.btag_combinedSecondaryVertex()>m_CSVOperatingPoint)?true:false;
	
      switch(flavour) {
        case 5: // b-jets
	  Hist("pt_bJet") -> Fill(jet.pt(),weight);
	  Hist("eta_bJet") -> Fill(jet.eta(),weight);
	  Hist("phi_bJet") -> Fill(jet.phi(),weight);
	  if (btag) {
	    Hist("pt_bJet_bTag") -> Fill(jet.pt(),weight);
	    Hist("eta_bJet_bTag") -> Fill(jet.eta(),weight);
	    Hist("phi_bJet_bTag") -> Fill(jet.phi(),weight);
	  }
	  break;
        case 4: // c-jets
	  Hist("pt_cJet") -> Fill(jet.pt(),weight);
	  Hist("eta_cJet") -> Fill(jet.eta(),weight);
	  Hist("phi_cJet") -> Fill(jet.phi(),weight);
	  if (btag) {
	    Hist("pt_cJet_bTag") -> Fill(jet.pt(),weight);
	    Hist("eta_cJet_bTag") -> Fill(jet.eta(),weight);
	    Hist("phi_cJet_bTag") -> Fill(jet.phi(),weight);
	  }
	  break;
        case 3: // s-quark
        case 2: // d-quark
        case 1: // u-quark
        case 21: // gluon
	  Hist("pt_lJet") -> Fill(jet.pt(),weight);
	  if(fabs(jet.eta())>=0&&fabs(jet.eta())<=0.8){
	    Hist("pt_lJet_e1") -> Fill(jet.pt(),weight);
	  }
	  if(fabs(jet.eta())>0.8&&fabs(jet.eta())<=1.6){
	    Hist("pt_lJet_e2") -> Fill(jet.pt(),weight);
	  }
	  if(fabs(jet.eta())>1.6&&fabs(jet.eta())<=2.4){
	    Hist("pt_lJet_e3") -> Fill(jet.pt(),weight);
	  }
	  Hist("eta_lJet") -> Fill(jet.eta(),weight);
	  Hist("phi_lJet") -> Fill(jet.phi(),weight);
	  if (btag) {
	    Hist("pt_lJet_bTag") -> Fill(jet.pt(),weight);
	    if(fabs(jet.eta())>=0&&fabs(jet.eta())<=0.8){
	      Hist("pt_lJet_e1_bTag") -> Fill(jet.pt(),weight);
	    }
	    if(fabs(jet.eta())>0.8&&fabs(jet.eta())<=1.6){
	      Hist("pt_lJet_e2_bTag") -> Fill(jet.pt(),weight);
	    }
	    if(fabs(jet.eta())>1.6&&fabs(jet.eta())<=2.4){
	      Hist("pt_lJet_e3_bTag") -> Fill(jet.pt(),weight);
	    }
	    Hist("eta_lJet_bTag") -> Fill(jet.eta(),weight);
	    Hist("phi_lJet_bTag") -> Fill(jet.phi(),weight);
	  }
	  break;
        default:
	  break;
      }
    }
}


void BTagEffHistsTopTag::Finish()
{
  // final calculations, like division and addition of certain histograms
}

